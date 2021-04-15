#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main () {
   FILE* fileIn;

   fileIn = fopen("./hashTable.bin", "rb");

   if (fileIn == NULL) {
      printf("Error al leer el archivo 'hashTable.bin'");
      return -1;
   }
   
   struct record {
      int sourceId;
      int destId;
      int hourOfDay;
      float meanTravelTime;
   };


   struct record *recordAux = malloc(sizeof(struct record));

   fread(&recordAux->sourceId, sizeof(recordAux->sourceId), 1, fileIn);
   fread(&recordAux->destId, sizeof(recordAux->destId), 1, fileIn);
   fread(&recordAux->hourOfDay, sizeof(recordAux->hourOfDay), 1, fileIn);
   fread(&recordAux->meanTravelTime, sizeof(recordAux->meanTravelTime), 1, fileIn);

   printf("%d %d %d %f\n", recordAux->sourceId, recordAux->destId, recordAux->hourOfDay, recordAux->meanTravelTime);

   fread(&recordAux->sourceId, sizeof(recordAux->sourceId), 1, fileIn);
   fread(&recordAux->destId, sizeof(recordAux->destId), 1, fileIn);
   fread(&recordAux->hourOfDay, sizeof(recordAux->hourOfDay), 1, fileIn);
   fread(&recordAux->meanTravelTime, sizeof(recordAux->meanTravelTime), 1, fileIn);
   
   printf("%d %d %d %f\n", recordAux->sourceId, recordAux->destId, recordAux->hourOfDay, recordAux->meanTravelTime);

   free(recordAux);
   fclose(fileIn);

   return 0;
}
