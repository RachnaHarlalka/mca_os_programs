#include<signal.h> //for signal() system call
#include<stdio.h> //for i/o statement

void handler_function(int signal_number)   //handler function for signals
{
    printf("\nSignal number : %d",signal_number);
    printf("\n");
    exit(0);

}
int main()
{
    printf("\nProcess id is %d\n",getpid());  //getting the process id
    signal(SIGHUP,handler_function);
    signal(SIGINT,handler_function);
    signal(SIGQUIT,handler_function);
    signal(SIGILL,handler_function);
    signal(SIGTRAP,handler_function);
    signal(SIGABRT,handler_function);
    signal(SIGBUS,handler_function);
    signal(SIGFPE,handler_function);
    signal(SIGKILL,handler_function);
    signal(SIGUSR1,handler_function);
    

    while(1) //infinte loop
    {
        printf("\nHello\n");
        sleep(1);
    }

return 0;

}