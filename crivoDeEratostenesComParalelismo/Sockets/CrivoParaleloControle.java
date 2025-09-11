import java.net.*;
import java.io.*;
import java.util.*;
import java.util.Vector;



public class CrivoParaleloControle extends Thread{
    private ServerSocket serversocket;

    Listner slaveListner[];
    Socket sockSlave[];
    static Slave slaves[];
    private int porta;
    public Vector<Boolean> marcados;
    int divisor = 0;
    int tamanhoVetor;
    int numeroDeFinalizados = 0;
    boolean available = true;
   
    CrivoParaleloControle(int porta,int numThreads) throws IOException{
        this.porta = porta;
        this.serversocket = new ServerSocket(porta); 

        this.marcados = new Vector<Boolean>();

        this.sockSlave = new Socket[numThreads];
        this.slaveListner = new Listner[numThreads];
    }

     private void mostraSequencia(){
        for (int i = 0; i < this.marcados.size(); i++) {
            if (this.marcados.get(i)) {
                System.out.print("("+i+") ");
            }else{
                System.out.print(i+" ");
            }          
        }
        System.out.println();
    }

    private void atualizaDivisor(){
        if(divisor>=0){
            if(this.divisor != 0){
                int proxDivisor = this.divisor;
                while (!checaProxsimoDivisor(proxDivisor)){
                    proxDivisor ++;
                };
    
                if(fimDoCrivo(proxDivisor))
                    this.divisor = -1;
                else
                    this.divisor = proxDivisor;
            }else{
                this.divisor = 2;
            }
        }
    }

    private boolean checaProxsimoDivisor(int num){
        return !this.marcados.get(num)&& this.divisor!=num;
    }

    protected boolean fimDoCrivo(int divisor){
        return (divisor * divisor > marcados.size()-1);
    }


    void inicializaVetorDeMarcados(){
        for (int i = 0; i < this.tamanhoVetor; i++) {
            this.marcados.add(new Boolean(false));
        }
        this.marcados.set(0,true);
        this.marcados.set(1,true);
    }

    public synchronized boolean enviaMensagemPara(Mensagem msg) throws IOException  {
        available = false;
        String remetente = msg.getRemetente();
        
        boolean fim;

        atualizaDivisor();

        int index =  Integer.parseInt(remetente);
        String resposta;

        if(this.divisor>0)
        {
            resposta = Integer.toString(this.divisor);
            fim = false;
        }else{
           
            resposta = "fim" ;
            fim = true;
        }
        
        slaveListner[index].saida().writeObject(new Mensagem(resposta, "0"));
        available = true;
        return fim;
    }

    public void estabeleceConexao() throws IOException {

        
        for (int i = 0; i < slaveListner.length; i++) {
            
            this.sockSlave[i] = serversocket.accept();
            slaveListner[i] = new Listner(this.sockSlave[i], this, i);
            slaveListner[i].start();

        }


    }

    public static void main(String[] args) throws IOException, InterruptedException {


        Scanner teclado = new Scanner(System.in);

        System.out.println("Entre com a quantidade de threads: ");
		int numThreads = teclado.nextInt();

        

        CrivoParaleloControle servidor = new CrivoParaleloControle(12345,numThreads);
        System.out.println("Entre com o valor máximo: ");
		servidor.tamanhoVetor = teclado.nextInt() + 1;

        slaves = new Slave[numThreads];

        for (int i = 0; i < slaves.length; i++) {
            slaves[i] =  new Slave("127.0.0.1", 12345, servidor, i);
            slaves[i].start();
        }

        servidor.inicializaVetorDeMarcados();
        servidor.estabeleceConexao();

        while(servidor.numeroDeFinalizados<numThreads){
            Thread.sleep(50);
        }

        servidor.serversocket.close();

        // servidor.mostraSequencia();
       
    }

}

class Listner extends Thread {
    private Socket sock;
    private boolean fim;
    private CrivoParaleloControle server;
    public ObjectInputStream streamEntrada;
    public ObjectOutputStream streamSaida;
    int id;
    
    public Listner(Socket sock, CrivoParaleloControle server,int id) throws IOException  {
        this.sock = sock;
        this.server = server;
        this.id = id;
        fim = false;
        estabeleceConexao(); 
    }
    
    public void finaliza() {
        fim = true;
    }

    void estabeleceConexao() throws IOException{
        streamSaida = new ObjectOutputStream(this.sock.getOutputStream());
        streamEntrada = new ObjectInputStream(this.sock.getInputStream());
    }
    
    
    public ObjectInputStream entrada() {
        return streamEntrada;
    }

    public ObjectOutputStream saida() {
        return streamSaida;
    }

    
    public void run() {
        try {
           
            Mensagem msg;
            while (!fim) { 
            
                msg = (Mensagem) streamEntrada.readObject();
                
                fim = server.enviaMensagemPara(msg);
                 
            } 
            streamEntrada.close();
            streamSaida.close();
            this.sock.close();
            this.server.numeroDeFinalizados++;
        } catch (Exception e) {
                System.err.println("Erro: " + e.getMessage());
            
        }
    }
}

class Slave extends Thread { 

    int id;
    Socket mySocket;
    protected ObjectInputStream streamEntrada;
    protected ObjectOutputStream streamSaida;
    protected boolean fim;
    CrivoParaleloControle server;
    int divisor;
    //ThreadEntrada entrada;

    Slave(String ip, int porta, CrivoParaleloControle server, int id) throws IOException {
        this.id = id;
        mySocket = new Socket(ip, porta);
        this.server = server;
    }

    void estabeleceConexao() throws IOException{
        streamSaida = new ObjectOutputStream(mySocket.getOutputStream());
        streamEntrada = new ObjectInputStream(mySocket.getInputStream());
    }

    private void marcaNaoPrimo(int naoPrimo){
        if(naoPrimo != this.divisor)
		    this.server.marcados.set(naoPrimo,true);
	}

    void finaliza() throws IOException {
        streamSaida.close();
        streamEntrada.close();
        mySocket.close();
        this.fim = true;
    }

    private void filtraMultiplos(){
        for (int i = this.divisor*this.divisor; i < this.server.marcados.size(); i+=this.divisor) {
                this.marcaNaoPrimo(i);
        }
    }

    private void atualizaMeuNumero(Mensagem msg){
        this.divisor = Integer.parseInt(msg.getMensagem());
        
    }

    public void enviaMensagem(Mensagem msg) throws IOException {
        streamSaida.writeObject(msg);
    }

    @Override
    public void run() {
        try {
            estabeleceConexao();
            Thread.sleep(1000);

            Mensagem msgToSend = new Mensagem("novo-numero",String.valueOf(id),"0");
            Mensagem msgToRecive;
            while(!this.fim){
                this.enviaMensagem(msgToSend);
                
                msgToRecive = (Mensagem)streamEntrada.readObject();

                if (!msgToRecive.getMensagem().equals("fim")){
                    
                    this.atualizaMeuNumero(msgToRecive);
                    this.filtraMultiplos();
                    System.out.println("Slave " + id + "  iterou sobre:" + this.divisor);
                }else{
                    this.finaliza();
                }
            }
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }// TODO Auto-generated method stub
        catch (ClassNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        
    }
    
}
