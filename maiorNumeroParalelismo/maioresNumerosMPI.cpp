#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
// size of array

using namespace std;

void achaOsDoisMaiores(int * numeros,int &maior1,int &maior2, int tam){
	for(int i = 0; i < tam; i++ ){
			if(numeros[i] > maior1){
				if(maior1> maior2){
					maior2=maior1;
				}
				maior1=numeros[i];
			}
			if(maior1>=maior2 && numeros[i] != maior1){
				if(numeros[i] > maior2){
					maior2=numeros[i];
				}
			}
		}
}

// Temporary array for slave process


int main(int argc, char* argv[])
{
    
   
    int *a;
    int *a_escravo;
	int pid, np, n,
		elements_per_process,
		n_elements_recieved;

	double starttime, endtime;

	srand (time(NULL));
	// np -> no. of processes
	// pid -> process id

	MPI_Status status;

	// Creation of parallel processes
	MPI_Init(&argc, &argv);

	// find out process ID,
	// and how many processes were started
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	// master process
	if (pid == 0) {
		int index, i;
        cout << "Entre com o tamanho do vetor: ";
		
       	starttime = MPI_Wtime();
        cin >> n;
        a = new int[n];
		elements_per_process = n / np;
        

         for(int i=0;i<n;i++)
            a[i]=rand()%10000;
        
        
         for(int i=0;i<n;i++)
            cout<<"Elementos indice["<<i<<"] "<<a[i]<<endl;
      
		// check if more than 1 processes are run
		if (np > 1) {
			// distributes the portion of array
			// to child processes to calculate
			// their partial sums
			for (i = 1; i < np - 1; i++) {
				index = i * elements_per_process;      
				MPI_Send(&elements_per_process,
						1, MPI_INT, i, 0,
						MPI_COMM_WORLD);
				MPI_Send(&a[index],
						elements_per_process,
						MPI_INT, i, 0,
						MPI_COMM_WORLD);
			}

			// last process adds remaining elements
			index = i * elements_per_process;
			int elements_left = n - index;
			MPI_Send(&elements_left,
					1, MPI_INT,
					i, 0,
					MPI_COMM_WORLD);
			MPI_Send(&a[index],
					elements_left,
					MPI_INT, i, 0,
					MPI_COMM_WORLD);
		}

        int maior1 = 0;
        int maior2 = 0;
		// master process add its own sub array
        achaOsDoisMaiores(a,maior1,maior2,elements_per_process);
		
		int *maioresDosMaiores = new int [2*np];

		maioresDosMaiores[0] = maior1;
		maioresDosMaiores[1] = maior2;
		// collects partial sums from other processes
       int tmp[2];
		for (i = 1; i < np; i++) {
			MPI_Recv(&tmp, 2, MPI_INT,
					MPI_ANY_SOURCE, 0,
					MPI_COMM_WORLD,
					&status);
			int sender = status.MPI_SOURCE;
			int index = i*2;
			maioresDosMaiores[index] = tmp[0];
			maioresDosMaiores[index+1] = tmp[1];
		}

		maior1 = maior2 = 0;

		achaOsDoisMaiores(maioresDosMaiores,maior1,maior2,np*2);
		endtime   = MPI_Wtime();
		printf("maior 1 : %d\n", maior1);
		printf("maior 2 : %d\n", maior2);
        printf("Levou %f segundos\n",endtime-starttime);
		
	}
	// slave processes
	else {
		MPI_Recv(&n_elements_recieved,
				1, MPI_INT, 0, 0,
				MPI_COMM_WORLD,
				&status);

		a_escravo = new int [n_elements_recieved];		// stores the received array segment
		// in local array a2
		MPI_Recv(&a_escravo[0], n_elements_recieved,
				MPI_INT, 0, 0,
				MPI_COMM_WORLD,
				&status);

		// calculates its partial sum
        int maior1 = 0;
        int maior2 = 0;

        achaOsDoisMaiores(a_escravo,maior1,maior2,n_elements_recieved);
        
        int maiores[] = {maior1, maior2};

		// sends the partial sum to the root process
		MPI_Send(&maiores[0], 2, MPI_INT,0, 0, MPI_COMM_WORLD);

	}

	// cleans up all MPI state before exit of process
	MPI_Finalize();

	return 0;
}
