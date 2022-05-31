#include<stdio.h>
#include<sys/stat.h>  //FOR mkfifo() SYSTEM CALL
#include <fcntl.h>  //FOR RDONLY() AND WRONGLY
#include <unistd.h>  //for close,read, write calls
#include<string.h>

#define size 50

int main()
{
    int fileDescriptor;
    char *fifopath = "/tmp/fifopath";
    char arr1[size],arr2[size]; //CHARACTER ARRAY TO STORE INPUT GIVEN BY PROGRAM 2
    // char arr2[]="ACKNOWLEDGEMENT"; //CHARACTER ARRAY TO STORE ACHNOWLEDGEMENT
    mkfifo(fifopath,0666);  //CREATING FIFO HAVING BOTH READING AND WRITING PERMISSIONS
    printf("\n\n...........csm21005...........\n\n");
    printf(" Displaying Program 2\n\n");

    while (1)
    {
    
        fileDescriptor = open(fifopath,O_WRONLY);  //OPEN FIFO IN WRITE ONLY MODE
        printf("Enter a message for program 1 : "); //TAKE USER INPUT
        fgets(arr2,80,stdin);  //read the user data
        printf("\n");
        write(fileDescriptor,arr2,strlen(arr2)+1); //WRITE TO FIFO
        close(fileDescriptor); //CLOSING FILE DESCRIPTOR

        // sleep(5);

        fileDescriptor=open(fifopath,O_RDONLY);   //OPEN FIFO IN READ ONLY MODE
        read(fileDescriptor,arr1,sizeof(arr1));  //Read Acknowledgement from FIFO
        printf("Program 1 replies : %s \n\n",arr1);  // READ THE ACK RECIEVED FROM PROGRAM 1
        close(fileDescriptor); //CLOSING FILE DESCRIPTOR

    }
    return 0;

}