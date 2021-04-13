#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 1000
         
struct record {
   int sourceId;
   int destId;
   int hourOfDay;
   float meanTravelTime;
};

int main () {
   
   FILE* fileIn;   
   FILE* fileOut;

   char line[MAX_SIZE];
   char* token;

   fileIn = fopen("./unprocessedData.csv", "r");
   fileOut = fopen("./hashTable.txt", "w");

   if (fileIn == NULL) {
      printf("Error al leer el archivo 'unprocessedData'");
      return -1;
   }

   int i = 0;

   while(/*!feof(fileIn)*/i < 4) {
      fgets(line, MAX_SIZE, fileIn);

      token = strtok(line, ","); 

      struct record currRecord; 

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

         token = strtok(NULL, ",");

         ++j;
      }

      printf("Current record: %d %d %d %f\n", currRecord.sourceId,
                currRecord.destId, currRecord.hourOfDay, currRecord.meanTravelTime);
      
      i++;
   }

   fclose( fileIn ); 

   return 0;
}
