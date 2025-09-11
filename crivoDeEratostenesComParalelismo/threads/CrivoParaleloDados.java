import java.math.BigInteger;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

/**
 * CrivoSequencial
 */
public class CrivoParaleloDados extends Thread{

    static private boolean marcados[];
    
    private int inicio;
    private int fim;

    static private Integer divisor = 2;

    CrivoParaleloDados(int indice, int intervalo){
        this.setPosicao(indice,intervalo);
    }

    public void run() {				
		this.filtraMultiplos();
	}

    static private boolean estaMarcado(int numero){
        return (marcados[numero]);
    }

    private void marcaNaoPrimo(int multiplo){
        marcados[multiplo] = true;;
    }

    private void setPosicao(int i, int resultado){

        this.inicio = i*resultado;
        this.fim = (i+1) * resultado - 1;
    }

    static private void marcaZeroOuUm(){
            marcados[0] = true;
            marcados[1] = true;
    }

    static private Integer pegaProximoDivisor(int tamanhoVetor){
        for (Integer i = divisor; i.compareTo(tamanhoVetor) <= 0; i++) {
            if(!estaMarcado(i) && isNotDivisor(i)){
                return i;
            }
        }
        return tamanhoVetor;
    }

    static private boolean isNotDivisor(int num){
        return num != divisor;
    }

    private boolean isDivisivel(int num){
        return num % divisor == 0;
    }

    private void filtraMultiplos(){
        for (int i = this.inicio; i <= this.fim; i++) {
            if(!estaMarcado(i) && this.isDivisivel(i) && isNotDivisor(i))
                this.marcaNaoPrimo(i);
        }
    }

    static private boolean fimDoCrivo(int tam){
        return (divisor * divisor < tam);
    }

    // private void mostraSequencia(){
    //     System.out.print("thread indice ["+this.inicio+"] :");
    //     for (int i = this.inicio; i <= this.fim; i++) {
    //         if (estaMarcado(i)) {
    //             System.out.print("("+i+") ");
    //         }else{
    //             System.out.print(i+" ");
    //         }          
    //     }
    //     System.out.println();
    // }


    public static void main(String[] args)  throws InterruptedException {

        Scanner teclado = new Scanner(System.in);
		int numeroThreadsEscolhido;

        Integer resultado, tamanhoVetor;

        System.out.println("Entre com a quantidade de threads: ");
		numeroThreadsEscolhido = teclado.nextInt();

        System.out.println("Entre com o valor máximo: ");
		tamanhoVetor = teclado.nextInt();

        teclado.close();
        
        marcados = new boolean [tamanhoVetor + 1];

        marcaZeroOuUm();

        
        CrivoParaleloDados[] threads = new CrivoParaleloDados[numeroThreadsEscolhido];
        
        resultado = tamanhoVetor/numeroThreadsEscolhido;
       
        long tempo1, tempo2; 
       
        tempo1 = System.nanoTime(); 
        while (fimDoCrivo(tamanhoVetor)) {

            for (int i = 0; i < numeroThreadsEscolhido; i++) {
                threads[i] = new CrivoParaleloDados(i,resultado);
            }

            threads[numeroThreadsEscolhido-1].fim = tamanhoVetor;

            System.out.println("divisor: "+ divisor);
            //-----------Parte paralela-------------------
			for(int j = 0; j < numeroThreadsEscolhido; j++)
            threads[j].start();
            
            for(int j = 0; j < numeroThreadsEscolhido; j++)
            threads[j].join();
            //-----------Parte paralela-------------------
            // for(int j = 0; j < numeroThreadsEscolhido; j++)
            // threads[j].mostraSequencia();
            
            divisor = pegaProximoDivisor(tamanhoVetor); 
        }
        tempo2 = System.nanoTime(); 
        System.out.print("N = " + numeroThreadsEscolhido);
        System.out.println("\tTempo = " + String.valueOf((tempo2 - tempo1)/1000000) + " ms");
    }
}