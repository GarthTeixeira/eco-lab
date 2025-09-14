
if [ "$#" -lt 2 ]; then
    echo "Uso: $0 <tamanho do vetor> <número de processos>" 
    exit 1
fi

if [ "$2" -gt "$1" ]; then
    echo "O número de processos deve ser menor ou igual ao tamanho do vetor."
    exit 1
fi

if [ "$#" -eq 4 ]; then
    echo "Uso: $0 <tamanho do vetor> <número de processos> <quantidade de números> <faixa inicial> <faixa final>" 
    exit 1
fi

tamanho_vetor=$1
numero_processos=$2

echo "Tamanho do vetor: $tamanho_vetor"
echo "Número de processos: $numero_processos"

numero_de_buscas=2
limite_inferior=0
limite_superior=10000

if [ "$#" -ge 3 ]; then
    echo "Quantidade de números a serem encontrados: $3"

    if [ "$1" -lt "$3" ]; then
        echo "O tamanho do vetor deve ser maior ou igual à quantidade de números a serem encontrados."
        exit 1
    fi

    if [ "$4" -ge "$5" ]; then
        echo "Limite inferior ($4) deve ser menor que limite superior ($5)"
        exit 1
    fi

    echo "Faixa de números: $4 a $5"

    numero_de_buscas=$3
    limite_inferior=$4
    limite_superior=$5
fi

g++ maioresNumerosSerial.cpp -o serial.out || { echo "❌ Erro ao compilar o programa serial"; exit 1; }
saida_string=$(./serial.out "$tamanho_vetor" "$numero_de_buscas" "$limite_inferior" "$limite_superior") 
saida_array=($saida_string)

tempo_serial=${saida_array[-1]}
elementos_resultado=("${saida_array[@]:0:numero_de_buscas}")

