import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

/**
 * CrivoSequencial
 */
public class CrivoSequencial {

    private Set<Integer> marcados = new HashSet<Integer>();
    private int tam;
    private int divisor = 2;

    private CrivoSequencial(int tam){
        this.tam = tam;
        this.marcados.add(0);
        this.marcados.add(1);
    }

    private boolean estaMarcado(int numero){
        return (this.marcados.contains(numero));
    }


    private void marcaNaoPrimo(int multiplo){
            this.marcados.add(multiplo);
    }

    private void pegaProximoDivisor(){
        for (int i = this.divisor; this.fimDoCrivo(); i++) {
            if(!estaMarcado(i)){
                this.divisor = i;
                this.filtraMultiplos();
                //this.mostraSequencia();
            } 
        }
    }

    private void filtraMultiplos(){
        for (int i = this.divisor*this.divisor; i <= this.tam; i+=divisor) {
            if(!this.estaMarcado(i))
            this.marcaNaoPrimo(i);
        }
    }

    private boolean fimDoCrivo(){
        return (this.divisor * this.divisor < this.tam);
    }

    private void mostraSequencia(){
        for (int i = 0; i <= this.tam; i++) {
            if (this.estaMarcado(i)) {
                System.out.print("("+i+") ");
            }else{
                System.out.print(i+" ");
            }          
        }
        System.out.println();
    }

    public static void main(String[] args) {

        Scanner teclado = new Scanner(System.in);
        System.out.println("Entre com o valor máximo: ");
		int tamanhoVetor = teclado.nextInt();
        teclado.close();
        CrivoSequencial crivo = new CrivoSequencial(tamanhoVetor);
        long tempo1, tempo2; 
        tempo1 = System.nanoTime(); 
        crivo.pegaProximoDivisor();
        tempo2 = System.nanoTime(); 
        System.out.println("\tTempo = " + String.valueOf((tempo2 - tempo1)/1000000) + " ms");
    }
}