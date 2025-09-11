# Cálculo de pi com programação paralela
 
 Para a prática de metodologias de proframação paralela, decidi resolver o problema da série de taylor por meio desta, usando o paralelismo de dados com duas ferramentas do C/C++, o opneMP e a biblioteca Phtreads
 
 ## OpenMP
 
 O programa implementado com openMP, faz uma varredura na máquina local mostrando o número de threads disponiveis. Em seguida da a opção de até quantas threads pode se dividir baseado no número de processadores, o usuário pode escolhar o número ou escolher com todos, logo será rodado diagnósticos com o tempo de processamento de cada um.
 
 - **Comando para compilar** :
 ```
 g++ -fopenmp sumTaylor.cpp - o <arquivo_saida>
 ```
 
  ## pthread
 
 O programa implementado com pthread permite que o usuário possa escolhar o número de threads, logo será rodado diagnósticos com o tempo de processamento.
 
  - **Comando para compilar** :
 ```
 g++ -pthread sumTaylor.cpp - o <arquivo_saida>
 ```
 
