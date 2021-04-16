#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "record.h"

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
   int i = 0;

   record_t *mainRecord = (record_t *) malloc(sizeof(record_t)); 

   while(!feof(fileIn)) {
      fgets(line, MAX_SIZE, fileIn);

      token = strtok(line, ","); 
      
      record_t *currRecord = (record_t *) malloc(sizeof(record_t)); 
     
      int j = 0;

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

      if (i == 0) { 
         memcpy(mainRecord, currRecord, sizeof(record_t));
      } else {

         record_t *temp = mainRecord;

         while (temp->next) {
            temp = temp->next;
         }
         
         temp->next = (record_t *) malloc(sizeof(record_t)); 
         memcpy(temp->next, currRecord, sizeof(record_t)); 
      }
      
      free(currRecord);

      i++;
   }
  
   record_t *temp = mainRecord;

   while(temp != NULL) {
      printf("Current: %d %d %d %f\n", temp->sourceId, temp->destId, temp->hourOfDay, temp->meanTravelTime);

      recordRead_t toWrite;
      toWrite.sourceId = temp->sourceId;
      toWrite.destId = temp->destId;
      toWrite.hourOfDay = temp->hourOfDay;
      toWrite.meanTravelTime = temp->meanTravelTime;

      fwrite(&toWrite, sizeof(toWrite), 1, fileOut);
      temp = temp->next;
   }

   printf("NULL\n");

   free( temp );
   free( mainRecord );
   
   fclose( fileIn ); 
   fclose( fileOut );

   return 0;
}
