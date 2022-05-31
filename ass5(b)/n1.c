#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include<sys/types.h>
#include<unistd.h>
#include <stdlib.h>

#define KEY 0x1111
  
int main()
{
    // ftok to generate unique key
    key_t key = ftok("shmfile",65);
  
    // shmget returns an identifier in shmid
    int shmid = shmget(key,1024,0666|IPC_CREAT);
  
    // shmat to attach to shared memory
    int *str = shmat(shmid,NULL,0);
  	
  	//Store pid in shared memory
  	*str = getpid();
	 
    printf("Data written in memory: %d\n",*str);
      
    //detach from shared memory 
    shmdt(str);
  
    return 0;
}