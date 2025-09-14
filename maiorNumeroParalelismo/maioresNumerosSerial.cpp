#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // escolhemos o último elemento como pivô
    int i = low - 1;       // índice do menor elemento

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) { // se elemento menor ou igual ao pivô
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]); // coloca o pivô na posição correta
    return i + 1;
}

// Função principal do Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // particiona o vetor

        // Ordena recursivamente as subpartes
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


void criarArquivoDeSaidas(ofstream &arquivo){
    arquivo.open("dado_de_busca.txt");
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo para escrita." << endl;
        exit(1);
    }
}



int main(int argc, char* argv[]) {

    ofstream arquivo;
    criarArquivoDeSaidas(arquivo);

    int tamanho_vetor, numero_buscas, limite_inferior, limite_superor;

    tamanho_vetor = atoi(argv[1]);
    numero_buscas = atoi(argv[2]);
    limite_inferior = atoi(argv[3]);
    limite_superor = atoi(argv[4]);

    vector<int> numeros(tamanho_vetor);
    srand(time(NULL));

    for (int i = 0; i < tamanho_vetor; i++) {
        numeros[i] = limite_inferior + rand() % (limite_superor - limite_inferior + 1);
        arquivo << numeros[i] << " ";
    }
    arquivo.close();

    clock_t start = clock();
    quickSort(&numeros[0], 0, numeros.size() - 1);

    for (int i = numeros.size() - 1; i >= numeros.size() - numero_buscas  ; i--){
        cout << numeros[i] << " ";
    }

    clock_t end = clock();
    double tempo = double(end - start) / CLOCKS_PER_SEC;
    cout << " "<< tempo <<"s"<<endl;

    return 0;
}
