import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;
import java.util.Vector;


public class CrivoParaleloControle extends Thread {

    public int id, inicio, fim;
    static private boolean marcados[];
	static private Vector<Integer> primosDisponiveis = new Vector<Integer>();
    static Integer threadsFinalizadas = 0;

	private CrivoParaleloControle(int id, int inicio, int fim) {
		this.id = id;	
		this.inicio = inicio;
		this.fim = fim;
	}

    public void resetInicio(int novoInicio){
        this.inicio = novoInicio;
    }

	public void run(){
        try {

            while (fimDoCrivo(this.inicio,this.fim)) {
                
                for(int i = this.inicio*this.inicio; i <= this.fim; i+=this.inicio)
                    this.marcaNaoPrimo(i);  
                //this.mostra();
                synchronized(primosDisponiveis){
                    if(!primosDisponiveis.isEmpty()){
                        this.inicio = primosDisponiveis.get(0);
                        primosDisponiveis.removeElement(this.inicio);
                    }
                }
            }
            
        } catch (Exception e) {
            
        }

    
        System.out.println("thread [" + this.id + "] saiu do loop");

        synchronized(threadsFinalizadas){
            threadsFinalizadas++;
        }
      
	}

    public synchronized void pegaNovoInicio(){
        if(!primosDisponiveis.isEmpty()){
            this.inicio = primosDisponiveis.get(0);
            primosDisponiveis.removeElement(this.inicio);
        }
    } 

    static synchronized void adicionaNovoPrimo(int primo){
        primosDisponiveis.add(primo);
        primosDisponiveis.removeIf(p->estaMarcado(p));
    } 

	private void marcaNaoPrimo(int naoPrimo){
		marcados[naoPrimo] = true;
	}

	static private boolean estaMarcado(int numero){
        return marcados[numero];
    }

	static private void marcaZeroUm(){
		marcados[0]=true;
		marcados[1]=true;
}

	private void mostra(){
		System.out.println("thread indice ["+ this.id + "] procurou por "+this.inicio);
	}

	static private void mostraSequencia(Vector<CrivoParaleloControle> threads, int tamanhoVetor){

        System.out.print("Primos restantes: ");

        for (int i = 0; i < primosDisponiveis.size(); i++) {
            System.out.print(primosDisponiveis.get(i)+" ");
        }
        System.out.print("\n Numeros marcados: ");
        for (int i = 0; i <= tamanhoVetor; i++) {
            if (estaMarcado(i)) {
                System.out.print("("+i+") ");
            }else{
                System.out.print(i+" ");
            }          
        }
        System.out.println();
    }

	static public boolean fimDoCrivo(int num, int tam){
        return Math.pow(num, 2) < tam;
    }
    
	public static void main(String[] args) throws InterruptedException {
 
        //Semaphore sem = new Semaphore(1);
		Scanner teclado = new Scanner(System.in);
        int tamanhoVetor;

        System.out.println("Entre com a quantidade de threads: ");
		int numThreads = teclado.nextInt();

        System.out.println("Entre com o valor máximo: ");
		tamanhoVetor = teclado.nextInt() + 1;

        marcados = new boolean [tamanhoVetor];

        teclado.close();

		Vector<CrivoParaleloControle> threads = new Vector<CrivoParaleloControle>(); 

		marcaZeroUm();

        Integer i =2, k=0;

        long tempo1, tempo2; 
       
        tempo1 = System.nanoTime(); 
		
		for (i = 2,k=0; i<tamanhoVetor; i++ ) {
			if(!estaMarcado(i) ){
                if (k<numThreads){
                    marcados[i*i]=true;
				    threads.add(new CrivoParaleloControle(k+1,i,tamanhoVetor));
				    threads.get(k).start();
				    k++;
                }else{
                    synchronized(primosDisponiveis){
                        primosDisponiveis.add(i);
                        primosDisponiveis.removeIf(p->estaMarcado(p));
                    }
                }
               
            }

           
        }
        
		for (int index = 0;index<threads.size();index++)
        {	
            threads.get(index).join();
        }

        tempo2 = System.nanoTime(); 
        System.out.print("N = " + numThreads);
        System.out.println("\tTempo = " + String.valueOf((tempo2 - tempo1)/1000000) + " ms");
		
        //mostraSequencia(threads, tamanhoVetor);
	}

}
