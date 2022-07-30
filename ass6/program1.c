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
   struct sembuf arrayOfStruct;
   size_t nsem = 1;

   semId = semget(key, nsem, 0666 | IPC_CREAT); //creating a semaphore set with key, number of semaphore element and permission
   if (semId < 0)
   {
      printf("\nSorry !! smaphore can't be created !!\n");
      exit(1);
   }

   printf("Press enter to lock the critical section: ");
   getchar();

   semctl(semId,0,SETVAL,1); 			//setting value to semaphore

   arrayOfStruct.sem_num = 0;      //Semaphore number in the range 0 to (nsems - 1)
   arrayOfStruct.sem_op = -1;                //lock applied
   arrayOfStruct.sem_flg = 0;

   status = semop(semId, &arrayOfStruct, nsem); // performing operation on semaphore

   if (status == -1)
   {
      exit(1);  //exit unsuccessfully
   }

   printf("Critical section is locked\n");

   fd = open("shared.txt", O_RDONLY); // open file in Read only mode
   if (fd < 0)                      // check if file is opened or not
   {
      exit(1); //exit unsuccessfully
   }

   read(fd, buffer, sizeof(buffer));               
   printf("\nData read from shared.txt: %s\n\n", buffer); 
   close(fd);                                      

   printf("Press enter to unlock the critical section: ");
   getchar();

   arrayOfStruct.sem_num = 0;
   arrayOfStruct.sem_op = 1; // lock released
   arrayOfStruct.sem_flg = 0;

   status= semop(semId, &arrayOfStruct, nsem);
   if (status == -1)
   {
      exit(1); //exit unsuccessfully
   }
   printf("Critical section unlocked\n");

   printf("Press enter only when program 2 has completed reading : ");
   getchar();

   semctl(semId, 0, IPC_RMID); // removing the semaphore
   printf("\nSemaphore removed successfully !!\n");

   return 0;
}