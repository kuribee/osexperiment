#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

void* calculate_pi(void* arg)
{
    unsigned int seed=time(NULL);

    int circle_points=0;
    int square_points=0;

    int intervals=*((int*)arg);
    double pi;

    for(int i=0;i<intervals*intervals;++i)
    {
        double rand_x=(double)rand_r(&seed)/RAND_MAX;
        double rand_y=(double)rand_r(&seed)/RAND_MAX;

        if((rand_x*rand_x+rand_y*rand_y)<=1)
        {
            circle_points++;
        }
        square_points++;
    }
    pi=(double)(4.0*circle_points)/square_points;

    printf("The estimated PI is %lf in %d times\n",\
    pi,intervals*intervals);

    pthread_exit(0);//The thread finish normally or abnormally
}

int main(int argc,char const *argv[])
{
    clock_t start,delta;
    double time_used;
    start=clock();

    pthread_t calculate_pi_threads[10];

    int args[10];
    for(int i=0;i<10;++i)
    {
        args[i]=1000*(i+1);
        pthread_create(calculate_pi_threads+i,NULL,calculate_pi,args+i);
    }
    for(int i=0;i<10;++i)
    {
        pthread_join(calculate_pi_threads[i],NULL);
    }
    delta=clock()-start;
    printf("The time taken in total : %lf seconds\n",(double)delta/CLOCKS_PER_SEC);
    return 0;
}