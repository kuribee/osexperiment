#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

void calculate_pi(int intervals)
{
    unsigned int seed=time(NULL);

    int circle_points=0;
    int square_points=0;

    double pi;

    for(int i=0;i<intervals*intervals;++i)
    {
        double rand_x=(double)rand()/RAND_MAX;
        double rand_y=(double)rand()/RAND_MAX;

        if((rand_x*rand_x+rand_y*rand_y)<=1)
        {
            circle_points++;
        }
        square_points++;
    }
    pi=(double)(4.0*circle_points)/square_points;

    printf("The estimated PI is %lf in %d times\n",\
    pi,intervals*intervals);
}

int main(int argc,char const *argv[])
{
    clock_t start,delta;
    double time_used;
    start=clock();

    #pragma omp parallel for num_threads(10)
    for(int i=0;i<10;++i)
    {
        calculate_pi(1000*(i+1));
    }
    delta=clock()-start;
    printf("The time taken in total : %lf seconds\n",(double)delta/CLOCKS_PER_SEC);
    return 0;
}