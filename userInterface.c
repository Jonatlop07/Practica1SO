#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>

#define ORIGIN_INPUT 1
#define DEST_INPUT 2
#define HOUR_INPUT 3
#define MID_TRAVEL_TIME 4
#define EXIT 5

int IdMemory;
key_t key =1234;
int *memory=NULL;

/*
ideaParaElFuturo:
podriamos enviar 4 enteros y que ese 4 me indique si el algoritmo de busqueda termino o no, si no termino 
hacemos un sleep(1) y volvemos a evaluar, si termino... se sale de la funcion y se muestra el resultado 
del algoritmo de busqueda
 nota 2: el % al final de la memoria compartida se arregla aumentando en 1 el shmget 
 */

int sendData(int source, int dest , int hour){
  
   IdMemory = shmget (key, 3*sizeof(int), 0666 | IPC_CREAT);
   if (IdMemory == -1){
     printf( "\nfallo en el shmget\n" );
     return (1);
   }
   memory = (int *)shmat (IdMemory, 0, 0);
   if (memory == NULL){
     printf ( "\nfallo en el shmat\n" );
     return (1);
   }
   *memory = source;
   *(memory+1) = dest;
   *(memory+2) = hour;
   printf ("El origen enviado es : %d \n", *memory);
   printf ("El destino enviado es : %d \n", *(memory+1));
   printf ("La hora enviada es : %d \n", *(memory+2));
   return (0);
}

int main () {
   int option, source = 0, dest = 0, hour = 0;
   float time;

   printf( "Bienvenido\n\n" );
   
   do {
      printf("\n\n");
      printf( "1. Ingresar origen\n" );
      printf( "2. Ingresar destino\n" );
      printf( "3. Ingresar hora\n" );
      printf( "4. Buscar tiempo de viaje medio\n" );
      printf( "5. Salir\n" );
   
      scanf( "%i", &option );
      
      switch ( option ) {
         case ORIGIN_INPUT:
	    printf( "\nIngrese ID del origen:" );
	    scanf( "%i", &source );
            break;

	 case DEST_INPUT:
            printf( "\nIngrese ID del destino:" );
	    scanf( "%i", &dest );
            break;

	 case HOUR_INPUT:
            printf( "\nIngrese hora del dia:" );
	    scanf( "%i", &hour );
            break;

	 case MID_TRAVEL_TIME:
	    if(sendData(source,dest,hour)==0){
	       sleep(5);//tiempo de espera mientras recibe los datos el algoritmo de busqueda
               printf( "\nEl tiempo de viaje medio: ");
	       //printf("%f",time);
	    }
	    break;

	 case EXIT:
            shmdt ((char *)memory);
            shmctl (IdMemory, IPC_RMID, (struct shmid_ds *)NULL);
            printf( "\nHasta luego (UwU)  \n" );
	    exit ( 0 );
	    break;

         default:
	    printf("\nError, vuelva a digitar la opcion\n");
	    break;
      }

   } while ( 1 );

   return 0;
}
