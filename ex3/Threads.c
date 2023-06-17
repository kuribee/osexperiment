#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

int value=100;//共享

void * hello(void * arg)
{
    int a;//local var->STACK
    for(int i=0;i<3;++i)
    {
        printf("hello(%d)\n",value++);
        sleep(1);
    }
}

void * world(void * arg)
{
    //Can here read a?->NO!
    for(int i=0;i<3;++i)
    {
        printf("world(%d)\n",value++);
        sleep(2);
    }
}

int main()
{
    srand(time(NULL));
    pthread_t tid,tid2;

    
    pthread_create(&tid,NULL,hello,NULL);
    pthread_create(&tid2,NULL,world,NULL);
    
    
    //sleep(1);
    
    pthread_join(tid,NULL);
    pthread_join(tid2,NULL);

    printf("In main thread(%d)\n",value++);
   
    return 0;
}