#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int ticketAmount=2;
sem_t s;

void * ticketAgent(void* arg){

    sem_wait(&s);//P
    int t=ticketAmount;
    if(t>0)
    {
        printf("One ticket sold!\n");
        t--;
    }else{
        printf("Ticket sold out!!\n");
    }
    ticketAmount=t;
    sem_post(&s);//V
    
    
    pthread_exit(0);
}

int main(int argc,char const* argv[])
{
    sem_init(&s,0,1); 
    pthread_t ticketAgent_tid[2];
    for(int i=0;i<2;++i)
    {
        pthread_create(ticketAgent_tid+i,NULL,ticketAgent,NULL);
    }
    for(int i=0;i<2;++i)
    {
        pthread_join(ticketAgent_tid[i],NULL);
    }
    printf("The left ticket is %d\n",ticketAmount);
    sem_destroy(&s);
    return 0;
}