#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void main()
{
  key_t key = 1234;
  int IdMemory;
  int *memory = NULL;
  //listen
  do{
     IdMemory = shmget (key, 3*sizeof(int), 0666 );
     if (IdMemory == -1){
        printf( "\nfallo en shmget\n");
	sleep(1);
     }
  }while(IdMemory == -1);

  memory = (int *)shmat (IdMemory, 0, 0);
  if (memory == NULL){
     printf( "\nfallo en shmat\n" );
     exit(0);
  }
  printf( "\nLlego %d", *memory );
  printf( "\nLlego %d", *(memory+1) );
  printf( "\nLlego %d \n", *(memory+2) ); 

  if (IdMemory != -1){
    shmdt ((char *)memory);
  }
}
