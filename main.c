#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "record.h"

int main () {
   FILE* fileIn;

   fileIn = fopen("./hashTable.bin", "rb");

   if (fileIn == NULL) {
      printf("Error al leer el archivo 'hashTable.bin'");
      return -1;
   }

   recordRead_t aux;
   
   int i = 0;

   while (!feof(fileIn)) {
      fread(&aux, sizeof(recordRead_t), 1, fileIn);
      printf("%d: %d %d %d %f \n", i+1, aux.sourceId, aux.destId, aux.hourOfDay, aux.meanTravelTime);
      ++i;
   }

   fclose(fileIn);

   return 0;
}
