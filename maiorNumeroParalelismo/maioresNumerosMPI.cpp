#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void achaOsDoisMaiores(int* numeros, int& maior1, int& maior2, int tam) {
    for (int i = 0; i < tam; i++) {
        if (numeros[i] > maior1) {
            if (maior1 > maior2) {
                maior2 = maior1;
            }
            maior1 = numeros[i];
        }
        if (maior1 >= maior2 && numeros[i] != maior1) {
            if (numeros[i] > maior2) {
                maior2 = numeros[i];
            }
        }
    }
}

int main(int argc, char* argv[]) {
    int process_id, processes_num;
    int array_size = 0, elements_per_process, n_elements_received;
    double start_time, end_time;
    int* a_main = nullptr;
    int* a_worker = nullptr;

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
    MPI_Comm_size(MPI_COMM_WORLD, &processes_num);

    // ✅ ler argumento do tamanho do vetor
    if (process_id == 0) {
        if (argc < 2) {
            cerr << "Uso: mpirun -np <proc> ./programa <tamanho_vetor>\n";
            MPI_Abort(MPI_COMM_WORLD, 1);
            return 1;
        }
        array_size = atoi(argv[1]);
        if (array_size <= 0) {
            cerr << "Erro: tamanho do vetor deve ser > 0\n";
            MPI_Abort(MPI_COMM_WORLD, 1);
            return 1;
        }
    }

    // ✅ Broadcast para todos os processos saberem o tamanho do vetor
    MPI_Bcast(&array_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    elements_per_process = array_size / processes_num;

    if (process_id == 0) {
        start_time = MPI_Wtime();

        a_main = new int[array_size];
        srand(time(NULL));
        for (int i = 0; i < array_size; i++) {
            a_main[i] = rand() % 10000;
        }

        // Distribui para os workers
        for (int i = 1; i < processes_num; i++) {
            int start = i * elements_per_process;
            int count = (i == processes_num - 1) ? (array_size - start) : elements_per_process;

            MPI_Send(&count, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&a_main[start], count, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        // Root process calcula sua parte
        // int maior1 = 0, maior2 = 0;
        // achaOsDoisMaiores(a_main, maior1, maior2, elements_per_process);

        // vector<int> maioresDosMaiores(2 * processes_num);
        // maioresDosMaiores[0] = maior1;
        // maioresDosMaiores[1] = maior2;

        // int tmp[2];
        // for (int i = 1; i < processes_num; i++) {
        //     MPI_Recv(tmp, 2, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        //     int idx = i * 2;
        //     maioresDosMaiores[idx] = tmp[0];
        //     maioresDosMaiores[idx + 1] = tmp[1];
        // }

        // maior1 = maior2 = 0;
        // achaOsDoisMaiores(maioresDosMaiores.data(), maior1, maior2, processes_num * 2);

        // end_time = MPI_Wtime();

        // cout << "Maior 1: " << maior1 << endl;
        // cout << "Maior 2: " << maior2 << endl;
        // cout << "Tempo: " << (end_time - start_time) << " segundos" << endl;

        delete[] a_main;
    } else {
        // Worker process
        MPI_Recv(&n_elements_received, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        a_worker = new int[n_elements_received];
        MPI_Recv(a_worker, n_elements_received, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        // int maior1 = 0, maior2 = 0;
        // achaOsDoisMaiores(a_worker, maior1, maior2, n_elements_received);

        // int maiores[2] = {maior1, maior2};
        // MPI_Send(maiores, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);

        delete[] a_worker;
    }

    MPI_Finalize();
    return 0;
}
