#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "record.h"
#include <sys/shm.h>

#define TRUE 1
#define FALSE 0

int main () {

   FILE* fileInHashTable;
   FILE* fileInProcessedData;
   
   recordRead_t aux;
   
   int r, hash, sourceId, destId, hourOfDay;
   int notFound = FALSE;

   // variables for the shared memory comunication
   key_t key = 1234;
   int memoryId;
   int *memory = NULL;

   //listen shared Memory

   do{
      memoryId = shmget( key, 3 * sizeof( int ), 0666 );

      if ( memoryId == -1 ) {
         printf( "\nfallo en shmget\n" );
      	 sleep( 1 );
      }

   } while ( memoryId == -1 );

   memory = ( int * ) shmat( memoryId, 0, 0 );

   if ( memory == NULL ) {
      printf( "\nfallo en shmat\n" );
      exit( 0 );
   }

   sourceId = *memory;
   destId = *( memory + 1 );
   hourOfDay = *( memory + 2 ); 

   if ( memoryId != -1 ){
     shmdt( ( char * ) memory );
   }

   fileInHashTable = fopen( "./hashTable.bin", "rb" );
   fileInProcessedData = fopen( "./processedData.bin", "rb" );

   if ( fileInHashTable == NULL ) {
      printf( "Error al leer el archivo 'hashTable.bin'" );
      return -1;
   }

   if ( fileInProcessedData == NULL ) {
      printf( "Error al leer el archivo 'processedData.bin'" );
      return -1;
   }

   r = fseek( fileInHashTable, ( sourceId - 1 ) * sizeof( int ), SEEK_SET );

   if ( r < 0 ) {
      perror( "Error al buscar una determinada posición en el archivo 'hashTable.bin'" );
      return -1;
   }

   r = fread( &hash, sizeof( hash ), 1, fileInHashTable );
   
   if ( r <= 0 ) {
      perror( "Error al leer en el archivo 'hashTable.bin'" );
      return -1;
   }

   r = fseek( fileInProcessedData, hash * sizeof( recordRead_t ), SEEK_SET );

   if ( r < 0 ) {
      perror( "Error al buscar una determinada posición en el archivo 'processedData.bin'" );
      return -1;
   }

   //search algorithm
   do {
      r = fread( &aux, sizeof( aux ), 1, fileInProcessedData );

      if ( r <= 0 ) {
         perror( "Error al leer en el archivo 'processedData.bin'" );
         return -1;
      }

      if ( sourceId != aux.sourceId || feof( fileInProcessedData ) ) {
         notFound = TRUE;
         break;
      }

   } while ( destId != aux.destId || hourOfDay != aux.hourOfDay );

   if ( notFound ) printf( "NA\n" );
   else printf( "\n\n Tiempo de viaje medio: %.3f \n", aux.meanTravelTime );

   fclose( fileInHashTable );
   fclose( fileInProcessedData );

   return 0;
}
