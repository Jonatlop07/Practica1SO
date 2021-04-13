#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main () {
   char option;

   do {
      printf( "Bienvenido\n\n" );
      printf( "1. Ingresar origen" );
      printf( "2. Ingresar destino" );
      printf( "3. Ingresar hora" );
      printf( "4. Buscar tiempo de viaje medio" );
      printf( "5. Salir" );
   
      scantf( "%c", &option );

      switch ( option ) {
         case ORIGIN_INPUT:

         case DEST_INPUT:

         case HOUR_INPUT:

         case MID_TRAVEL_TIME:

         case EXIT:
            exit ( 0 );
         default:
      }

   } while ( true );

   return 0;
}
