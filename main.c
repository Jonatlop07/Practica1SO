#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "record.h"

#define TRUE 1
#define FALSE 0

int main () {

   FILE* fileInHashTable;
   FILE* fileInProcessedData;
   
   recordRead_t aux;
   
   int r, hash;
   int sourceId = 3, destId = 478, hod = 0;
   int notFound = FALSE;

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
   
   if ( r < 0 ) {
      perror( "Error al leer en el archivo 'hashTable.bin'" );
      return -1;
   }

   r = fseek( fileInProcessedData, hash * sizeof( recordRead_t ), SEEK_SET );

   if ( r < 0 ) {
      perror( "Error al buscar una determinada posición en el archivo 'processedData.bin'" );
      return -1;
   }

   do {
      r = fread( &aux, sizeof( aux ), 1, fileInProcessedData );

      if ( r < 0 ) {
         perror( "Error al leer en el archivo 'processedData.bin'" );
         return -1;
      }

      if ( sourceId != aux.sourceId || feof( fileInProcessedData ) ) {
         notFound = TRUE;
         break;
      }

   } while ( destId != aux.destId || hod != aux.hourOfDay );

   if ( notFound ) printf( "NA\n" );
   else printf( "Tiempo de viaje medio: %f\n", aux.meanTravelTime );

   fclose( fileInHashTable );
   fclose( fileInProcessedData );

   return 0;
}
