#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t s;

void * cars(void * argc)
{
    printf("(%u)I INTEND to pass the fork!\n",pthread_self());
    sleep(1);

    sem_wait(&s);
    printf("(%u)I am AT the fork!\n",pthread_self());
    sleep(1);
    

    printf("(%u)I have PASSED the fork!\n",pthread_self());
    sleep(1);
    
    sem_post(&s);
    pthread_exit(0);
}

int main(int argc,char const * argv[])
{
    sem_init(&s,0,2);
    pthread_t tid[5];

    for(int i=0;i<5;++i)
    {
        pthread_create(tid+i,NULL,cars,NULL);
    }
    for(int i=0;i<5;++i)
    {
        pthread_join(tid[i],NULL);
    }
    sem_destroy(&s);
    return 0;
}