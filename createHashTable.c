#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "record.h"

#define MAX_SIZE 1000

typedef struct record {
   int sourceId;
   int destId;
   int hourOfDay;
   float meanTravelTime;
   struct record *next;
}record_t;

typedef struct recordRead {
   int sourceId;
   int destId;
   int hourOfDay;
   float meanTravelTime;
}recordRead_t;

//functions

record_t *addRecord(record_t **list, record_t newRecord){
   if(*list == NULL){
      *list = (record_t *) malloc(sizeof(record_t));
      **list = newRecord;
   }else{
      record_t *aux = *list;

      while(aux->next != NULL){
         aux = aux->next;
      }

      aux->next = (record_t *) malloc(sizeof(record_t));
      *aux->next = newRecord;
   }
   return *list;
}

int main () {

   FILE* fileIn;   
   FILE* fileOut;

   char line[MAX_SIZE];
   char* token;
   //fileIn = fopen("./unprocessedData.csv", "r");
   fileIn = fopen("./hashTableIn.csv", "r");
   fileOut = fopen("./hashTable.bin", "wb");

   if (fileIn == NULL) {
      printf("Error al leer el archivo 'unprocessedData'");
      return -1;
   }

   record_t * hashTable[1160] = { NULL };

   while(!feof(fileIn)) {
      fgets(line, MAX_SIZE, fileIn);
      token = strtok(line, ",");

      record_t currRecord; 

      int j = 0;

      while(token != NULL && j <= 3) {
         switch (j) {
            case 0:
               currRecord.sourceId = atoi(token); 
               break;
            case 1:
               currRecord.destId = atoi(token);
               break;
            case 2:
               currRecord.hourOfDay = atoi(token);
               break;
            case 3:
               currRecord.meanTravelTime = atol(token);
               break;
         }

         currRecord.next = NULL;

         token = strtok(NULL, ",");

         ++j;

      }

      record_t *currList = addRecord(&hashTable[currRecord.sourceId - 1], currRecord);

   }
   for(int i=0;i<1160;i++){
      record_t *temp = hashTable[i];

      int j = 1;

      while(temp != NULL) {
         printf("(%d, %d): %d %d %d %f\n", i+1, j, temp->sourceId, temp->destId, temp->hourOfDay, temp->meanTravelTime);

         recordRead_t toWrite;
         toWrite.sourceId = temp->sourceId;
         toWrite.destId = temp->destId;
         toWrite.hourOfDay = temp->hourOfDay;
         toWrite.meanTravelTime = temp->meanTravelTime;

         fwrite(&toWrite, sizeof(toWrite), 1, fileOut);
         temp = temp->next;
         ++j;
      }
   }

   fclose( fileIn );
   fclose( fileOut );

   return 0;
}
