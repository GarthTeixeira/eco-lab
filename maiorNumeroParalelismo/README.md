# Encontrar maiores numeros com MPI
O programa a seguir utiliza da comunicação MPI para encontrar os 2 maiores números de um vetor, o alogritmo utiliza de paralelismo de dados dividindo o vetor pelo número de processamentos desejados.

## Pré requisitos

### OpenMPI
**Instalação**

```bash
sudo apt install openmpi
```

confira a versão instalada:

```bash
mpic++ --version
```

**Testando o programa**

Para compilar e executar o arquivo `testeMPI.cpp`, utilize os comandos abaixo:

```bash
mpic++ testeMPI.cpp -o testeMPI
mpirun -np 4 ./testeMPI
```

- Substitua `4` pelo número de processos desejado.
- Certifique-se de que o arquivo `testeMPI.cpp` está no mesmo diretório.

**Rode os scripts**

No conteúdo de `runAllAndCompare.sh` todos os scripts serão rodados.

```bash
runAllAndCompare.sh <tamanho_vetor> <numero_de_processos>
```

A quantidade de números a serem buscados por padrão é 2, os números serão sorteados, mas isso pode ser alterado com

```bash
runAllAndCompare.sh <tamanho_vetor> <numero_de_processos> <numro_de_buscas> <limite_inferior> <limite_superior>
```

**Documentação MPI**

[https://www.open-mpi.org/]