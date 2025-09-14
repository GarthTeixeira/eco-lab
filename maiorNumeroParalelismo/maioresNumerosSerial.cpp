#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

class Parametros {
    public:
        int tamanho_vetor;
        int numero_buscas;
        int limite_inferior;
        int limite_superior;

        Parametros(int t, int n, int li, int ls) 
            : tamanho_vetor(t), numero_buscas(n), limite_inferior(li), limite_superior(ls) {}

        Parametros(char* argv[]) {
            tamanho_vetor = atoi(argv[1]);
            numero_buscas = atoi(argv[2]);
            limite_inferior = atoi(argv[3]);
            limite_superior = atoi(argv[4]);
        }
};


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

void registrarNumerosNoArquivo(Parametros params, vector<int> &numeros) {
    ofstream arquivo;
    criarArquivoDeSaidas(arquivo);
    for (int i = 0; i < params.tamanho_vetor; i++) {
        numeros[i] = params.limite_inferior + rand() % (params.limite_superior - params.limite_inferior + 1);
        arquivo << numeros[i] << " ";
    }
    arquivo.close();
}



int main(int argc, char* argv[]) {

    Parametros params(argv);

    vector<int> numeros(params.tamanho_vetor);
    srand(time(NULL));

    registrarNumerosNoArquivo(params, numeros);

    clock_t start = clock();
    quickSort(&numeros[0], 0, numeros.size() - 1);

    for (int i = numeros.size() - 1; i >= numeros.size() - params.numero_buscas  ; i--){
        cout << numeros[i] << " ";
    }

    clock_t end = clock();
    double tempo = double(end - start) / CLOCKS_PER_SEC;
    cout << " "<< tempo <<"s"<<endl;

    return 0;
}
