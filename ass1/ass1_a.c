#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
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
      printf("\nHello, i am a parent pocesss !!");
      printf("\nprocess id of current process is %d\n", getpid());
      printf("\nprocess id of parent's process is %d\n", getppid());
    }
    else{
        printf("\nChild cannot be created !!");
    }
}
