#include<stdio.h>
#include<sys/sem.h> //for semget(),sembef and semaphore related system calls
#include<fcntl.h> //for RDONLY(),WRONLY()
#include<unistd.h> //for close(),read()
#include<stdlib.h> //for exit()

#define SIZE 50

int main()
{
   int fd,semId,status;
   char buffer[SIZE];
   key_t key=1705;
   struct sembuf sbuf;
   size_t nsem = 1;

   semId = semget(key, 1, 0666); //grab the semaphore set 

   if (semId < 0)
   {
      printf("\nSorry! semaphore can't be accessed\n");
      exit(1); //exit unsuccessfully
   }

   status = semctl(semId, 0, GETVAL); // get the semaphore value and return it

   if (status == 0)
   {
      printf("File is locked\n");
      exit(1); //exit unsuccessfully
   }

   fd = open("shared.txt", O_RDONLY); // opening file in Read only mode
   if (fd < 0)                      // checking if file is opened or not
   {
      exit(1); // exit unsuccessfully
   }

   read(fd, buffer, sizeof(buffer));             
   printf("\nData read from shared.txt: %s\n", buffer); 
   close(fd);                                   
   return 0;
}