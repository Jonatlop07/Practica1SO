#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "record.h"
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

record_t *addRecord(record_t *list, record_t *newRecord){
   
   record_t *aux;
   if(list == NULL){
      list = (record_t *)malloc(sizeof(record_t));
      memcpy(list, newRecord, sizeof(record_t));
   }else{
      aux = list;
      while(aux->next != NULL){
         aux = aux->next;
      }
      memcpy(aux->next, newRecord, sizeof(record_t));
      printf("Current2: %d %d %d %f\n", aux->next->sourceId, aux->next->destId, aux->next->hourOfDay, aux->next->meanTravelTime);
   }
   return list;
}


#define MAX_SIZE 1000

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

   int id = 0;
   record_t * hashTable[1160];

   //init hashTable
   for(int i=0;i<1160;i++){
      record_t *list;
      list = NULL;
      hashTable[i]=list;
   }
   //record_t *mainRecord = (record_t *) malloc(sizeof(record_t));

   while(!feof(fileIn)) {
      fgets(line, MAX_SIZE, fileIn);
      token = strtok(line, ",");
      record_t *currRecord = (record_t *) malloc(sizeof(record_t)); 
      int j = 0;
      int currSourceId,currDestId,currHourOfDay;
      float currMeanTravelTime;
      while(token != NULL && j <= 3) {
         switch (j) {
            case 0:
               currRecord->sourceId = atoi(token); 
               break;
            case 1:
               currRecord->destId = atoi(token);
               break;
            case 2:
               currRecord->hourOfDay = atoi(token);
               break;
            case 3:
               currRecord->meanTravelTime = atol(token);
               break;
         }

         currRecord->next = NULL;

         token = strtok(NULL, ",");

         ++j;

      }
      printf("%d\n",currRecord->sourceId);
      record_t *currList = hashTable[((currRecord->sourceId)-1)];
      if(currList == NULL)printf(" currlistNULL  ");
      currList = addRecord(currList, currRecord);

      record_t *temp = currList;
      while(temp != NULL) {
         printf("Current: %d %d %d %f\n", temp->sourceId, temp->destId, temp->hourOfDay, temp->meanTravelTime);
         temp = temp->next;
      }
    free(currRecord);
   }
   for(int i=0;i<1160;i++){
      record_t *temp = hashTable[i];
      while(temp != NULL) {
         printf("Current: %d %d %d %f\n", temp->sourceId, temp->destId, temp->hourOfDay, temp->meanTravelTime);

         recordRead_t toWrite;
         toWrite.sourceId = temp->sourceId;
         toWrite.destId = temp->destId;
         toWrite.hourOfDay = temp->hourOfDay;
         toWrite.meanTravelTime = temp->meanTravelTime;

         fwrite(&toWrite, sizeof(toWrite), 1, fileOut);
         temp = temp->next;
         //printf("NULL\n");
      }
      
   }
   fclose( fileIn );
   fclose( fileOut );

   return 0;
}
