#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HashTable.h"
#define NUM_PARAMS   8
#define TABLE_SIZE   5
#define INTEGER_TYPE 1

void freeIntegerType(void* intPtr);

int main()
{
   char** params = calloc(NUM_PARAMS, sizeof(char*));
   params[0] = malloc(255);
   strcpy(params[0], "host");
   params[1] = malloc(255);
   strcpy(params[1], "target");
   params[2] = malloc(255);
   strcpy(params[2], "compilerOption");
   params[3] = malloc(255);
   strcpy(params[3], "hostCompilerOption");
   params[4] = malloc(255);
   strcpy(params[4], "targetCompilerOption");
   params[5] = malloc(255);
   strcpy(params[5], "linkerOption");
   params[6] = malloc(255);
   strcpy(params[6], "hostLinkerOption");
   params[7] = malloc(255);
   strcpy(params[7], "targetLinkerOption");

   int values[NUM_PARAMS] = {1, 2, 3, 4, 5, 6, 7, 8};

   HashTable* table = malloc(sizeof(HashTable));
   initHashTable(table, INTEGER_TYPE, TABLE_SIZE);

   for (int i = 0; i < NUM_PARAMS; i++)
   {
      HashTableItem* item = malloc(sizeof(HashTableItem));
      item->key = params[i];
      item->data = &values[i];
      hash_insert(table, item, INTEGER_TYPE);
   }

   for (int i = 0; i < NUM_PARAMS; i++)
   {
      int* value = (int*)hash_lookup(table, params[i], INTEGER_TYPE);
      if (value != NULL)
      {
         printf("Table[%s] => %d\n", params[i], *value);
      }
   }

   printf("\n\n=============================================\n");
   printf("Looking up a bad key: APPLE\n");
   void* badValue = hash_lookup(table, "APPLE", INTEGER_TYPE);
   if (badValue == NULL)
   {
      printf("Was NULL\n");
   }
   else
   {
      printf("Bad Value: %d\n", *(int*)badValue);
   }
   printf("=============================================\n");

   HashTableItem* removed = hash_remove(table, "compilerOption", INTEGER_TYPE);
   if (removed != NULL)
   {
      free((char*)removed->key);
   }

   printIntegerHashTable(table, "The Best Table");

   freeHashTable(table, freeIntegerType, true, false);
   return 0;
}

void freeIntegerType(void* data) { free(data); }