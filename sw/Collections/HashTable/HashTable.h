#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>

typedef struct HashTableItem
{
   const char* key;
   void* data;
} HashTableItem;

typedef struct HashTable
{
   int type;
   unsigned int size;
   HashTableItem** items;
} HashTable;

#ifdef __cplusplus
extern "C"
{
#endif

   void initHashTable(HashTable* table, int type, int size);
   void freeHashTable(HashTable* table, void (*freeData)(void*), bool keysOnHeap, bool dataOnHeap);
   void* hash_lookup(const HashTable* table, const char* key, int type);
   bool hash_insert(HashTable* table, HashTableItem* item, int type);
   HashTableItem* hash_remove(HashTable* table, const char* key, int type);
   int hash_type(const HashTable* list);
   void printIntegerHashTable(const HashTable* table, const char* nameOfTable);

#ifdef __cplusplus
}
#endif

#endif