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



[https://www.open-mpi.org/]