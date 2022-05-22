#include<signal.h> //for signal() system call
#include<stdio.h> //for i/o statement

int main()
{
    pid_t pid;
    int signal_number;
    int status;
    printf("\nEnter the process id : ");
    scanf("%d",&pid);

//menu for signals
    printf("\n1. SIGHUP\n");
    printf("2. SIGINT\n");
    printf("3. SIGQUIT\n");
    printf("4. SIGILL\n");
    printf("5. SIGTRAP\n");
    printf("6. SIGABRT\n");
    printf("7. SIGBUS\n");
    printf("8. SIGFPE\n");
    printf("9. SIGKILL\n");
    printf("10. SIGUSR1\n");

    printf("Enter the signal number which you want to pass :");
    scanf("%d",&signal_number);

    status=kill(pid,signal_number); //if kill is successfull , it returns 0
                                    //otherwise it return -1

    if(status==0)
    {
        printf("\nKill signal sent successfully !!");
    }




}