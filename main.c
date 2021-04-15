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

   record_t *head = malloc(sizeof(record_t));
   record_t *recordAux = head;

   while (recordAux->next != NULL) {
      fread(&recordAux->sourceId, sizeof(recordAux->sourceId), 1, fileIn);
      fread(&recordAux->destId, sizeof(recordAux->destId), 1, fileIn);
      fread(&recordAux->hourOfDay, sizeof(recordAux->hourOfDay), 1, fileIn);
      fread(&recordAux->meanTravelTime, sizeof(recordAux->meanTravelTime), 1, fileIn);
      fread(&recordAux->next, sizeof(recordAux->next), 1, fileIn);
      recordAux = recordAux->next; 
   }

   record_t *temp = head;

   while(temp->next != NULL) {
      printf("%d %d %d %f\n", temp->sourceId, temp->destId, temp->hourOfDay, temp->meanTravelTime);
      printf("%p\n", &temp->next);
      temp = temp->next;
   }

   free(head);
   fclose(fileIn);

   return 0;
}
