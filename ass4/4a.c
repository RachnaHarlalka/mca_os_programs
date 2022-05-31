#include<signal.h> //for signal system call
#include<sys/types.h>  //for fork() system cal
#include<sys/wait.h> //for wait() system call
#include<stdio.h> //for i/o statements


void handler_function(int signal_number)
{
    int N;
    int a,b,c;
    int fd[2];
    int buffer[100];
    pipe(fd);   //creation of pipe
    if(pipe(fd)<0) //check if pipe is initialised successfully or not
    {
        printf("Error occured while initialising pipe\n");
        exit(1);
    }
    pid_t x = fork(); // to create a  child process
    pid_t id;

    if (x==0) // checking for child process
    {
        printf("\n  I am a Child Process\n");
        id = getpid();
        printf("  My process id is %d",id);
        printf("\n--------------------------\n");


        close(fd[0]);  //closing read end since its a write process

        printf("Enter the number of terms you want in fibonicci series : ");
        scanf("%d",&N);

        //sending the process id from child end
        write(fd[1],&id,sizeof(id));

        //Sending the number of terms from child end
        write(fd[1],&N,sizeof(N));
        a=0;
        b=1;
        //sending the value of a and b from child
        write(fd[1],&a,sizeof(a));
        write(fd[1],&b,sizeof(b));
        
        //fibonicci series
        for(int i=2;i<N;i++)
             {   
                c=a+b;
                write(fd[1],&c,sizeof(c));   //sending the fibonicci term from child to parent
                a=b;
                b=c;
             }
        write(fd[1],&signal_number,sizeof(signal_number));   //sending the signal number
        close(fd[1]);   //closing write end after writing
        exit(0);   // exit successfully
    }

    else if (x > 0) // check for parent process
    {
        wait(NULL);
        printf("\n  I am a Parent Process\n");
        printf("--------------------------\n");


        close(fd[1]);   //closing the write end since its a read process)

        read(fd[0],&id,sizeof(id)); //read process id from read end i.e parent process
        read(fd[0],&N,sizeof(N));   //read the no. of terms from read end
        printf("Process id of the child : %d", id);
        read(fd[0],buffer,100); // read fibonacci series in buffer from read end
        printf("\n\nFibonicci series : \n");
        for(int i=0;i<N;i++)
        {
            printf(" %d ",buffer[i]);
        }
        printf("\n\n");

        read(fd[0], &signal_number, sizeof(signal_number)); // read signal ID from read end
        printf("Signal number is %d\n\n", signal_number);
        close(fd[0]); //closing read end after reading
        exit(0);   // exit successfully
    }

    else        //check if error creating a child process
    {
        printf("\nError while creating child !!\n");
        exit(1); // exit unsuccessfully
    }
}
int main()
{
    signal(SIGINT,handler_function);
    while(1)
    {
        printf("\nHello ! Please interrupt me !!\n");
        sleep(1);
    }
    return 0;
}