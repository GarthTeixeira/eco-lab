#include <mpi.h>
#include <iostream>
#include <chrono>

using namespace std;

void setPosicao(int &inicio, int &fim, int i, int resultado){

    inicio = i*resultado;
    fim = (i+1) * resultado - 1;
}

void marcaZeroOuUm(bool* marcados ){
        marcados[0] = true;
        marcados[1] = true;
}

void marcaNaoPrimo(bool* marcados ,int posicao){
        marcados[posicao] = true;
}

bool estaMarcado(bool* marcados, int posicao){
    return marcados[posicao];
}

bool isDivisivel(int num, int divisor){
    return num % divisor == 0;
}

bool isNotDivisor(int num, int divisor){
    return num != divisor;
}

void filtraMultipolos( bool* marcados,int num, int divisor, int posicao){
    //cout<<"Num :"<<num<<"divisor :"<<divisor <<"posicao"<<posicao<<endl;
    if(!estaMarcado(marcados,posicao) && isDivisivel(num,divisor) && isNotDivisor(num, divisor))
        marcaNaoPrimo(marcados,posicao);
}

bool fimDoCrivo(int divisor,int tam,int rank){
    cout<<rank<<" no fim do crivo"<< divisor << tam <<endl;
    return (divisor * divisor < tam);
}

int pegaProximoDivisor(int divisor,bool* marcados,int tamanhoSequencia){
    for (int i = divisor; i <= (tamanhoSequencia); i++) {
        if(!estaMarcado(marcados,i) && isNotDivisor(i,divisor)){
            return i;
        }
    }
    return tamanhoSequencia;
}

void mostraSequencia(bool* marcados, int tamanhoSequencia){
    for (int i = 0; i < tamanhoSequencia; i++) {
        if (estaMarcado(marcados,i)) {
            cout<<"("<<i<<") ";
        }else{
            cout<<i<<" ";
        }          
    }
    cout<<endl;
}

int main( int argc, char *argv[] )
{
    int tamanhoSequencia;
    
    bool *vetorDeMarcados ;
    bool *divisaoDoVetor ;

	int rank, size, inicio, fim , resultado, divisor,resto;
    MPI_Status status;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );	
	//fsdfsdfd

    if(rank == 0){

        cout<<"Selecione tamanho da sequencia:";
        cin>>tamanhoSequencia;
        resultado = tamanhoSequencia/size;
        vetorDeMarcados = new bool[resultado * size];
        resto = tamanhoSequencia%size;
        divisaoDoVetor = new bool[resultado];
        divisor = 2;
        cout<<"divisao de :"<<resultado<<"+"<<resto<<endl;
        
        for (int i = 0; i < tamanhoSequencia; i++)
        {
            vetorDeMarcados[i]=false;
        }
        marcaZeroOuUm(vetorDeMarcados);

     } 
     //

        MPI_Bcast(&divisor,1,MPI_INT,0,MPI_COMM_WORLD);
        MPI_Bcast(&resultado,1,MPI_INT,0,MPI_COMM_WORLD);
        MPI_Bcast(&tamanhoSequencia,1,MPI_INT,0,MPI_COMM_WORLD);

        while (fimDoCrivo(divisor,tamanhoSequencia,rank))
        {
            MPI_Scatter(vetorDeMarcados,resultado,MPI_C_BOOL,divisaoDoVetor,resultado,MPI_C_BOOL,0,MPI_COMM_WORLD);
                for (int i = 0 ; i < resultado; i++)
                {
                    int num = i + rank*resultado;
                    filtraMultipolos(divisaoDoVetor,num,divisor,i);
                }   

            MPI_Gather(divisaoDoVetor,resultado,MPI_C_BOOL,vetorDeMarcados,resultado,MPI_C_BOOL,0,MPI_COMM_WORLD);
            
            if(rank == 0){
                divisor = pegaProximoDivisor(divisor,vetorDeMarcados,resultado*size);
            }

            MPI_Bcast(&divisor,1,MPI_INT,0,MPI_COMM_WORLD);
        }
        if(rank == 0){
            mostraSequencia(vetorDeMarcados,tamanhoSequencia);
        }

        MPI_Barrier(MPI_COMM_WORLD);
	    MPI_Finalize();
    
	return 0;
}
