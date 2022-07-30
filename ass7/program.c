
#include<stdio.h>   //for input output functions
#include<unistd.h>   //for getpid
#include<fcntl.h>    //for fcntl(),O_RDWR etc
#include<stdlib.h>   //for exit()

#define SIZE 100

int main()
{
    int fd;  //declaring the file descriptor
    char buffer[SIZE];
    struct flock lock;   //initialising the structure flock
    fd = open("sharedFile.txt",O_RDWR); //open a file named demo.txt
    if(fd<0)
    {
        printf("\nError !\n");
        exit(1); //unsuccessfull termnation
    }
    lock.l_type=F_WRLCK;
    lock.l_whence=SEEK_SET; //SEEK_SET moves the file pointer position to the beginning of the file
    lock.l_start=0;//since we used SEEK_SET, l_start=0 //This is the starting offset in bytes of the lock, relative to l_whence.
                     //l_start is relative to l_whence and l.whence is relative to the whole file
    lock.l_len=0;      //This is the length of the lock region in bytes (which starts from l_start which is relative to l_whence)
    lock.l_pid=getpid();    //getting the pid

    if(fcntl(fd,F_SETLK,&lock)==-1)   //locking file, if already locked it will return -1
        {
          printf("\nFile is locked !!\n");
        }
    else
        {
        read(fd,buffer,sizeof(buffer)); //reading from the shared file
        printf("\nData from sharedFile.txt : %s\n",buffer); //displaying data read from shared file
        }
    printf("\nPress enter to unlock !!\n");
    getchar();
    lock.l_type=F_UNLCK;


    if(fcntl(fd,F_SETLK,&lock)!=-1)   //unlocking file
        {
        printf("\nLock unlocked !!\n");
        }
    close(fd);   //closing file descriptor
    return 0;

}