#include <stdio.h>
#include <stdlib.h>

#include "HashTable.h"
#define NUM_PARAMS   8
#define TABLE_SIZE   10
#define INTEGER_TYPE 1

void freeIntegerType(void* intPtr);

int main()
{
   char* params[NUM_PARAMS] = {"host", "target", "compilerOption", "hostCompilerOption", "targetCompilerOption", "linkerOption", "hostLinkerOption", "targetLinkerOption"};
   int values[NUM_PARAMS] = {1, 2, 3, 4, 5, 6, 7, 8};

   HashTable* table = malloc(sizeof(HashTable));
   initHashTable(table, INTEGER_TYPE, TABLE_SIZE);

   for (int i = 0; i < NUM_PARAMS; i++)
   {
      HashTableItem item = {.key = params[i], .data = &values[i]};
      hash_insert(table, &item, INTEGER_TYPE);
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

   printIntegerHashTable(table, "The Best Table");

   freeHashTable(table, freeIntegerType);
   return 0;
}

void freeIntegerType(void* intPtr) {}