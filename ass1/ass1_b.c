#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>


#include<unistd.h>

int main()
{

    pid_t pid= fork();
    if(pid==0)
    {
        printf("\nHello, i am a child pocesss !!");
        printf("\nprocess id of current process is %d", getpid());
         printf("\nprocess id of parent's process is %d", getppid());
    }
    else if(pid>0)
    {
        wait(NULL);
      printf("\nHello, i am a parent pocesss !!");
      printf("\nprocess id of current process is %d", getpid());
      printf("\nprocess id of parent's process is %d", getppid());
    }
    else{
        printf("\nChild cannot be created !!");
    }
}
