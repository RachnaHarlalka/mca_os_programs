#include<stdio.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>


int main()
{
    key_t key = 1705; //UNIQUE ID GIVEN TO THE SHARED MEMORY
    int shmId = shmget(key,1024,0666); //CREATION SHARED MEMORY IF NOT CREATED, HAVING KEY AS 1705, SIZE:1024 BYTES HAVING BOTH READ AND WRITE PERMISSION
   
    int *shared_memory = shmat(shmId,NULL,0);       // ATTACHING THE MEMORY TO PROCESS ADDRESS SPACE

    printf("Data read from the shared memory : %d\n",*shared_memory); //DATA READ FROM THE SHARED MEMORY

    shmdt(shared_memory); //DETACHING THE SHARED MEMORY

    shmctl(shmId,IPC_RMID,NULL); //DESTROYED THE SHARED MEMORY

    return 0;


}