#include<iostream>
#include <string>
#include<omp.h>

static long num_steps = 100000000;
double step;

int main()
{
    int i, start, qtdThreads, nthreads, count;
    double sum, pi = 0.0;
    
    step = 1.0/(double)num_steps;

    double ti,tf;

    std::string select;

    int num_max_threads = omp_get_max_threads();


    std::cout<<"Set the number of process ( the max numeber of your machine is " <<num_max_threads<<")"<<std::endl;
    std::cout<<"You can type \"all\" to run with all the process though:"<<std::endl;

    std::cin>>select;

    if(select == "all"){
        start = 1;
        count = num_max_threads;
    }else{
        qtdThreads = stoi(select);
       
        start = count = qtdThreads;
    }

    if (start>=1 && start<=num_max_threads)
    {
        for (int j = start; j <= count; j++)
        {
            std::cout<<"Process with "<<j<<" process"<<std::endl;
            ti = omp_get_wtime();
            omp_set_num_threads(j);
            
            #pragma omp parallel 
            {
                double x;
                #pragma omp for reduction(+:sum)
                    for (i = 0; i < num_steps; i++)
                    {
                        x = (i+0.5)*step;
                        sum += 4.0/(1.0+x*x);
                    }
            }
            
            pi = step*sum;
            
            tf = omp_get_wtime();
            
            std::cout<<"Value of  pi: "<<pi<<std::endl;
            std::cout<<"Time: "<<tf-ti<<std::endl;
            sum = 0.0; 
        }
    }else{
         std::cout<<"Value out of range!"<<std::endl;
    }
    
    return 0;
}
