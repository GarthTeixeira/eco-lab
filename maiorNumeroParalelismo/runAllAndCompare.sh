
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

    numero_de_buscas=$3
    limite_inferior=$4
    limite_superior=$5

    elementos_por_processo=$((tamanho_vetor/numero_processos))
    
    resto_elementos_por_processo=$((tamanho_vetor%numero_processos))

    if [ "$resto_elementos_por_processo" -eq 0 ]; then
        if [ "$elementos_por_processo" -lt "$numero_de_buscas" ]; then
            echo "O número de processos é muito grande para o tamanho do vetor e a quantidade de números a serem encontrados."
            echo "Elementos por processo ($tamanho_vetor / $numero_processos) = $elementos_por_processo"
            exit 1
        fi
    else
        if [ "$resto_elementos_por_processo" -lt "$numero_de_buscas" ]; then
            echo "O número de processos é muito grande para o tamanho do vetor e a quantidade de números a serem encontrados."
            echo "O resto de elementos por processo ($tamanho_vetor % $numero_processos) = $elementos_por_processo"
            exit 1
        fi
    fi

    echo "Elementos por processo: $elementos_por_processo"

    if [ "$tamanho_vetor" -lt "$numero_de_buscas" ]; then
        echo "O tamanho do vetor deve ser maior ou igual à quantidade de números a serem encontrados."
        exit 1
    fi

    if [ "$limite_inferior" -ge "$limite_superior" ]; then
        echo "Limite inferior ($limite_inferior) deve ser menor que limite superior ($limite_superior)."
        exit 1
    fi

    echo "Faixa de números: $limite_inferior a $limite_superior"

fi

g++ maioresNumerosSerial.cpp -o serial.out || { echo "❌ Erro ao compilar o programa serial"; exit 1; }
saida_string=$(./serial.out "$tamanho_vetor" "$numero_de_buscas" "$limite_inferior" "$limite_superior") 
saida_array=($saida_string)

tempo_serial=${saida_array[-1]}
elementos_resultado=("${saida_array[@]:0:numero_de_buscas}")
echo "✅ Programa serial executado com sucesso em $tempo_serial segundos."
echo "Números encontrados (serial): ${elementos_resultado[*]}"

