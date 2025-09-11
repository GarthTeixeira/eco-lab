#include <iostream>
#include <omp.h>
#include <unordered_set>

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

int main (int argc, char *argv[])
{
    int qtdThreads, id, tamanhoSequencia;

    cout<<"Selecione o numero de threads:";
    cin>>qtdThreads;

    cout<<"Selecione tamanho da sequencia:";
    cin>>tamanhoSequencia;

    std::unordered_set<int> marcados = std::unordered_set<int>();

    double ti,tf;

    ti = omp_get_wtime();
    marcaZeroOuUm(marcados);
    int divisor = 2;
    int intervalo = tamanhoSequencia/qtdThreads; 


    while(fimDoCrivo(divisor,tamanhoSequencia))
    {
        omp_set_num_threads(qtdThreads);
        #pragma omp parallel for
            for (int i = 0 ; i <= tamanhoSequencia; i++)
            {
                filtraMultipolos(marcados,i,divisor);
            }   

        divisor = pegaProximoDivisor(divisor,marcados,tamanhoSequencia);
        std::cout<<"Divisor: "<<divisor<<std::endl;
    }
    tf = omp_get_wtime();
    //mostraSequencia(marcados,tamanhoSequencia);
    std::cout<<"Usando: "<<qtdThreads<<" threads"<<std::endl;
    std::cout<<"Tempo gasto: "<<tf-ti<<std::endl;
    return 0;
}
