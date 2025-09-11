#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <chrono>
#include <pthread.h>


struct args_struct {
    int id;
    int nthrds;
    long long num_steps;
    long double step;
    long double answer;
};

double long pi = 0.0;
pthread_mutex_t mutex;

void* realizaCalculo(void *args){

    struct args_struct *arg_ptr = (args_struct*) args;
    
    int id = arg_ptr->id;
    int nthrds = arg_ptr->nthrds;
    long long num_steps = arg_ptr->num_steps;
    long double step = arg_ptr->step;

    //std::cout<<"tarefa em progresso 1... \n";
    long double x,sum=0.0;
      for ( long long i = id; i < num_steps; i=i+nthrds)
        {
            x = (i+0.5)*step;
            sum += 4.0/(1.0+x*x);
            //std::cout<<sum<<"\n";
        }
    //std::cout<<"tarefa em progresso 3... \n";
    
    pthread_mutex_lock(&mutex);
    pi += sum*step;
    pthread_mutex_unlock(&mutex);
    std::cout<<" thread[" <<id<<"] terminou \n";
    return 0;    
}


int main(int argc, char const *argv[])
{
    long long num_steps = 10000000000;
    long double step = 1.0/(double)num_steps;
    int numThreads;
    std::cout<<"Numero de threads \n";
    std::cin >> numThreads;
    

    pthread_t *tids = new pthread_t[numThreads];
    pthread_mutex_init(&mutex,NULL);

    struct args_struct *args = new args_struct [numThreads];

    auto ti = std::chrono::high_resolution_clock::now();

    std::cout<<"crando threads... \n";
    for (size_t i = 0; i < numThreads; i++)
    {
        args[i].id = i;
        args[i].nthrds = numThreads;
        args[i].num_steps = num_steps;
        args[i].step = step;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tids[i],&attr,&realizaCalculo,&args[i]);
    }

    std::cout<<"Realizando calculo... \n";
    
    for (size_t i = 0; i < numThreads; i++)
    {
        pthread_join(tids[i],NULL);
    }
    auto tf = std::chrono::high_resolution_clock::now();
    std::cout<<"O resultado: "<<pi<<std::endl;
    std::cout<<"Duração (ms): "<< std::chrono::duration_cast<std::chrono::milliseconds>(tf-ti).count()<<std::endl;
    /* code */
    return 0;
}
