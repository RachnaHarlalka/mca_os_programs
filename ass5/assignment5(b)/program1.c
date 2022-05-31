#include<stdio.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>


int main()
{
    key_t key = 1705; //UNIQUE ID GIVEN TO THE SHARED MEMORY
    int shmId = shmget(key,1024,0666|IPC_CREAT); //CREATION OF THE SHARED MEMORY HAVING KEY AS 1705, SIZE:1024 BYTES HAVING BOTH READ AND WRITE PERMISSION
    if(shmId==-1)
    {
        exit(1);
    }

    int *shared_memory = shmat(shmId,NULL,0);       // ATTACHING THE MEMORY TO PROCESS ADDRESS SPACE

    *shared_memory = getpid();  //GETTING THE PROCESS ID AND STORING IN THE SHARED MEMORY

    printf("Data stored in the shared memory i.e \nprocess id is : %d\n",*shared_memory);

    shmdt(shared_memory); //DETACHING THE SHARED MEMORY


}