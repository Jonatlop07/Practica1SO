#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <time.h>

#define ORIGIN_INPUT 1
#define DEST_INPUT 2
#define HOUR_INPUT 3
#define MID_TRAVEL_TIME 4
#define EXIT 5

//Global variables for the shared memory comunication between unparented processes

int memoryId;

key_t key = 1234;

int *memory = NULL;

int sendData( int sourceId, int destId, int hourOfDay ) {
  
   memoryId = shmget( key, 3 * sizeof( int ), 0666 | IPC_CREAT );

   if ( memoryId == -1 ) {
     printf( "\nfallo en el shmget\n" );
     return 1;
   }

   memory = ( int * ) shmat( memoryId, 0, 0 );

   if ( memory == NULL ) {
     printf ( "\nfallo en el shmat\n" );
     return 1;
   }

   *memory = sourceId;
   *( memory + 1 ) = destId;
   *( memory + 2 ) = hourOfDay;

   return 0;
}

int main () {

   int option, sourceId = 0, destId = 0, hourOfDay = 0;
   
   do {
      system( "clear" );
      printf( "Bienvenido (UwU)\n\n" );
      printf( "Menu:\n");
      printf( "1. Ingresar origen\n" );
      printf( "2. Ingresar destino\n" );
      printf( "3. Ingresar hora\n" );
      printf( "4. Buscar tiempo de viaje medio\n" );
      printf( "5. Salir\n" );
      printf( "\nIngrese el numero de la opcion deseada:  " );
      scanf( "%i", &option );
      
      switch ( option ) {
         case ORIGIN_INPUT:
	         system( "clear" );
	         printf( "\nIngrese ID del origen:  " );
	         scanf( "%i", &sourceId );
            break;
	      case DEST_INPUT:
	         system( "clear" );
            printf( "\nIngrese ID del destino:  " );
	         scanf( "%i", &destId );
            break;
	      case HOUR_INPUT:
	         system( "clear" );
            printf( "\nIngrese hora del dia:  " );
	         scanf( "%i", &hourOfDay );
            break;
	      case MID_TRAVEL_TIME:
	         system( "clear" );
            clock_t begin, end;
            begin = clock();

	         if( sendData( sourceId, destId, hourOfDay ) == 0 ){
	            system( "./searchRecord" );

               end = clock();

               double duration = ( double ) ( end - begin ) / CLOCKS_PER_SEC;

               printf( "\n\nLa busqueda tomo %2.6f segundos.\n", duration );
	            printf( "\nPresione Enter para continuar" );

	            getchar();
	            getchar();
	         }

	         break;
	      case EXIT:
            shmdt( ( char * ) memory );
            shmctl( memoryId, IPC_RMID, ( struct shmid_ds * ) NULL );
            printf( "\nHasta luego (UwU)\n" );
	         exit ( 0 );
	         break;
         default:
	         printf( "\nError, vuelva a digitar la opcion\n" );
	         getchar();
	         getchar();
	         break;
      }

   } while ( 1 );

   return 0;
}
