#include <iostream>
#include <omp.h>
#include <unordered_set>
#include <queue>

using namespace std;


void setPosicao(int &inicio, int &fim, int i, int resultado){

    inicio = i*resultado;
    fim = (i+1) * resultado - 1;
}

void marcaZeroOuUm(std::unordered_set<int> &marcados ){
        marcados.emplace(0);
        marcados.emplace(1);
}

void marcaNaoPrimo(std::unordered_set<int> &marcados ,int multiplo){
        marcados.emplace(multiplo);
}

bool estaMarcado(std::unordered_set<int> marcados, int num){
    return marcados.count(num)>0;
}

bool isDivisivel(int num, int divisor){
    return num % divisor == 0;
}

bool isNotDivisor(int num, int divisor){
    return num != divisor;
}

void filtraMultipolos(std::unordered_set<int> &marcados,int num, int divisor){
    if(!estaMarcado(marcados,num) && isDivisivel(num,divisor) && isNotDivisor(num, divisor))
        marcaNaoPrimo(marcados,num);
}

bool fimDoCrivo(int divisor,int tam){
    return (divisor * divisor < tam);
}

int pegaProximoDivisor(int divisor,std::unordered_set<int> marcados,int tamanhoSequencia){
    for (int i = divisor; i <= (tamanhoSequencia); i++) {
        if(!estaMarcado(marcados,i) && isNotDivisor(i,divisor)){
            return i;
        }
    }
    return tamanhoSequencia;
}

void mostraSequencia(std::unordered_set<int> marcados, int tamanhoSequencia){
    for (int i = 0; i <= tamanhoSequencia; i++) {
        if (estaMarcado(marcados,i)) {
            cout<<"("<<i<<") ";
        }else{
            cout<<i<<" ";
        }          
    }
    cout<<endl;
}

int pegaProximoPrimo( std::unordered_set<int> marcados, int ultimoPrimo ){

    int proximoPrimo;
    for (proximoPrimo = ultimoPrimo +1; estaMarcado(marcados,proximoPrimo); proximoPrimo++)
    { }
    return proximoPrimo;
}

void realizaTarefa(std::unordered_set<int> &marcados, int ultimoPrimo, int tamanhoSequencia){
    
}

int main (int argc, char *argv[])
{
    int qtdThreads, id, tamanhoSequencia;

    cout<<"Selecione o numero de threads:";
    cin>>qtdThreads;

    cout<<"Selecione tamanho da sequencia:";
    cin>>tamanhoSequencia;

    std::unordered_set<int> marcados = std::unordered_set<int>();
    std::queue<int> primos = std::queue<int>();
    double ti,tf;


    ti = omp_get_wtime();
    marcaZeroOuUm(marcados);
    //pegaPrimeirosPrimos(primos);
    
    int ultimoPrimo = 1;
    // cout<<"UltimoPrimo"<<ultimoPrimo<<endl ;
    // int dummy = pegaProximoPrimo(marcados,ultimoPrimo);
    // cout<<"\nO que deveria ser "<<dummy ;

    omp_set_num_threads(qtdThreads);
    #pragma omp parallel shared(ultimoPrimo)
    { 
        int meuPrimo;
        int myThread = omp_get_num_threads();
         while(fimDoCrivo(ultimoPrimo,tamanhoSequencia)){

            #pragma omp critical 
                ultimoPrimo = pegaProximoPrimo(marcados,ultimoPrimo);

            meuPrimo = ultimoPrimo;
            for (int i = meuPrimo ; i <= tamanhoSequencia; i+=meuPrimo)
            {
                filtraMultipolos(marcados,i,meuPrimo);
            }
        }
    }
  
    tf = omp_get_wtime();
    //mostraSequencia(marcados,tamanhoSequencia);
    std::cout<<"Usando: "<<qtdThreads<<" threads"<<std::endl;
    std::cout<<"Tempo gasto: "<<tf-ti<<std::endl;
    return 0;
}
