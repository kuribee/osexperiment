#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>




int main()
{
    pid_t pid;
    pid_t cid;

    printf("Before fork Process id :%d\n",getpid());
    int value=100;
    cid=fork();

    if(cid==0){
        printf("Child process id (my parent pid is %d):%d\n",getppid(),getpid());
        for(int i=0;i<3;i++)    //300ciyoujiaoti
            printf("hello(%d)\n",value--);
        
    }else{
        printf("Parent process id :%d\n",getpid());
        for(int i=0;i<3;i++)
            printf("world(%d)\n",value++);

        
    }

    

    return 0;
}