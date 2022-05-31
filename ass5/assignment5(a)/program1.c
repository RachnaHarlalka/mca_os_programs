#include<stdio.h>
#include<sys/stat.h>  //FOR mkfifo() SYSTEM CALL
#include <fcntl.h>  //FOR RDONLY() AND WRONGLY
#include <unistd.h>  //for close,read, write calls
#include<string.h>


#define size 50
int main()
{
    int fileDescriptor;  //FILE DESCRIPTOR
    char *fifopath = "/tmp/fifopath";   //CREATING NAMED PIPE
    char arr1[size],arr2[size]; //CHARACTER ARRAY TO STORE READ AND WRITE MESSAGES
    mkfifo(fifopath,0666);  //CREATING FIFO HAVING BOTH READING AND WRITING PERMISSIONS
    printf("\n\n...........csm21005...........\n\n");
    printf(" Displaying Program 1\n\n");
    
    while(1)
    {
        fileDescriptor=open(fifopath,O_RDONLY); //OPEN FIFO IN READ ONLY MODE
        read(fileDescriptor,arr1,sizeof(arr1));  //READ FROM FIFO
        printf("Program 2 says : %s \n\n",arr1);  //PRINT THE MESSAGE THAT WE RECIEVED FROM PROGRAM 1
        close(fileDescriptor);   //CLOSING FILE DESCRIPTOR

        // sleep(1);

        fileDescriptor = open(fifopath,O_WRONLY); //OPEN FIFO IN WRITE ONLY MODE
        printf("\nGive reply to program 2 : ");   //TAKE USER INPUT
        fgets(arr2,80,stdin);  
        printf("\n");
        write(fileDescriptor,arr2,strlen(arr2)+1);  //WRITE TO FIFO
        close(fileDescriptor);  //CLOSING FILE DESCRIPTOR

    }
    return 0;
    

}

