#include<signal.h> //for signal() system call
#include<sys/types.h> //for fork() system call
#include<sys/wait.h> //for wait() system call
#include<stdio.h> //for i/o statement

void handler_function(int signal_number)
{
    pid_t x = fork(); // to create a  child process

    if (x==0) // checking for child process
    {
        printf("\nI am a Child Process\n");
        printf("My process id is %d",getpid()); // process id of child process
        printf("\nMy parent's process id is %d\n", getppid()); // process id of child's parent process
        exit(0);   // exit successfully
    }

    else if (x > 0) // check for parent process
    {
        wait(NULL);
         printf("\nI am a Parent Process\n");
        printf("My process id is %d",getpid()); // process id of child process
        printf("\nMy parent's process id is %d\n", getppid()); // process id of parent's parent process
        exit(0);   // exit successfully
    }

    else        //check if error creating a child process
    {
        printf("Error while creating child !!\n");
        exit(1); // exit unsuccessfully
    }
}

int main()
{
    signal(SIGINT,handler_function); // signal handling
    while(1)// infinite loop
        {
            printf("Hello ! Please Interrupt me !!\n");
            sleep(1);
        }

    return 0;
}

