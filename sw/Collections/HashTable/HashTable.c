#include "HashTable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////
//              Private Function Prototypes                         //
//////////////////////////////////////////////////////////////////////
unsigned int hash(const char* key, unsigned int tableSize);
int checkType(const HashTable* table, int type);

//////////////////////////////////////////////////////////////////////
//              Function Implementation Section                     //
//////////////////////////////////////////////////////////////////////
unsigned int hash(const char* key, unsigned int tableSize)
{
   int length = strlen(key);
   unsigned int value = 0;
   for (int i = 0; i < length; i++)
   {
      value += key[i];
      value = (value * key[i]) % tableSize;
   }
   return value;
}

int checkType(const HashTable* table, int type)
{
   if (table->type != type)
   {
      printf("Hash Table Type Error. Can not use type: %d for Hash Table of type: %d\n", type, table->type);
      return 1;
   }
   return 0;
}

void initHashTable(HashTable* table, int type, int size)
{
   HashTableItem** tableData = calloc(sizeof(HashTableItem*), size);
   table->type = type;
   table->size = size;
   table->items = tableData;
}

void freeHashTable(HashTable* table, void (*freeData)(void*), bool keysOnHeap, bool dataOnHeap)
{
   if (keysOnHeap || dataOnHeap)
   {
      for (int i = 0; i < table->size; i++)
      {
         if (table->items[i] != NULL)
         {
            if (keysOnHeap)
            {
               free((char*)table->items[i]->key);
            }
            if (dataOnHeap)
            {
               freeData(table->items[i]->data);
            }
         }
      }
   }
   free(table->items);
   free(table);
}

void* hash_lookup(const HashTable* table, const char* key, int type)
{
   int typeError = checkType(table, type);
   if (!typeError)
   {
      unsigned int index = hash(key, table->size);
      for (int i = 0; i < table->size; i++)
      {
         int indexToTry = (i + index) % table->size;
         if (table->items[indexToTry] != NULL)
         {
            if (strcmp(table->items[indexToTry]->key, key) == 0)
            {
               return table->items[indexToTry]->data;
            }
         }
      }
   }
   return NULL;
}

bool hash_insert(HashTable* table, HashTableItem* item, int type)
{
   int typeError = checkType(table, type);
   if (!typeError)
   {
      unsigned int index = hash(item->key, table->size);
      for (int i = 0; i < table->size; i++)
      {
         int indexToTry = (i + index) % table->size;
         if (table->items[indexToTry] == NULL)
         {
            table->items[indexToTry] = item;
            return true;
         }
      }
   }

   return false;
}

HashTableItem* hash_remove(HashTable* table, const char* key, int type)
{
   int typeError = checkType(table, type);
   if (!typeError)
   {
      unsigned int index = hash(key, table->size);
      for (int i = 0; i < table->size; i++)
      {
         int indexToTry = (i + index) % table->size;
         if (table->items[indexToTry] != NULL)
         {
            if (strcmp(table->items[indexToTry]->key, key) == 0)
            {
               HashTableItem* temp = table->items[indexToTry];
               table->items[indexToTry] = NULL;
               return temp;
            }
         }
      }
   }
   return NULL;
}

int hash_type(const HashTable* table) { return table->type; }

void printIntegerHashTable(const HashTable* table, const char* nameOfTable)
{
   printf("==============================================\n");
   printf("Printing Hash Table - %s\n", nameOfTable);
   printf("==============================================\n");
   printf("Size: %d\n", table->size);
   for (int i = 0; i < table->size; i++)
   {
      if (table->items[i] != NULL)
      {
         printf("Table[%d]: (%s, %d)\n", i, table->items[i]->key, *(int*)table->items[i]->data);
      }
      else
      {
         printf("Table[%d]: NULL\n", i);
      }
   }
}