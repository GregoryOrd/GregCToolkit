#include "LinkedList.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////
//              Private Function Prototypes                         //
//////////////////////////////////////////////////////////////////////
int checkType(const LinkedList* list, int type);
int checkIndex(const LinkedList* list, int index);

//////////////////////////////////////////////////////////////////////
//              Function Implementation Section                     //
//////////////////////////////////////////////////////////////////////

int checkType(const LinkedList* list, int type)
{
   if (list->dataType != type)
   {
      printf("Linked List Type Error. Can not use type: %d for Linked List of type: %d\n", type, list->dataType);
      return 1;
   }
   return 0;
}

int checkIndex(const LinkedList* list, int index)
{
   if (index >= list->size && list->size != 0)
   {
      printf("Linked List Index Out of Bounds. Can not access index: %d for Linked List of size: %d\n", index, list->size);
      return 1;
   }

   if (index < 0)
   {
      printf("Linked List Index Out of Bounds. Can not access index less than or equal to zero.\n");
      return 1;
   }
   return 0;
}

void initEmptyLinkedList(LinkedList* list, int type)
{
   list->dataType = type;
   list->size = 0;
   list->head = 0;
}

void freeLinkedList(LinkedList* list, void (*freeData)(void*))
{
   Node* itr = list->head;
   while (itr != 0)
   {
      Node* prev = itr;
      itr = itr->next;
      (*freeData)(prev->data);
      prev->next = 0;
      free(prev);
   }
   list->dataType = 0;
   list->size = 0;
   free(list);
}

int size_ll(const LinkedList* list, int type)
{
   int typeError = checkType(list, type);
   if (!typeError)
   {
      return list->size;
   }
   return -1;
}

int type_ll(const LinkedList* list) { return list->dataType; }

int insert_ll(LinkedList* list, void* data, int type, int index)
{
   bool uninitializedList = (list == NULL);
   if (uninitializedList)
   {
      list = malloc(sizeof(LinkedList));
      initEmptyLinkedList(list, type);
   }

   int typeError = checkType(list, type);
   int indexToCheck = index - 1;
   if (indexToCheck < 0)
   {
      indexToCheck = 0;
   }
   int indexError = checkIndex(list, indexToCheck);
   if (!typeError && !indexError)
   {
      Node* currentPtr = list->head;
      int i = 0;
      while (currentPtr != 0 && i < index)
      {
         i++;
         if (i > 1)
         {
            currentPtr = currentPtr->next;
         }
      }

      Node* newNode = malloc(sizeof(Node));
      newNode->data = data;
      newNode->next = 0;

      if (i == 0)
      {
         newNode->next = list->head;
         list->head = newNode;
      }
      else
      {
         newNode->next = currentPtr->next;
         currentPtr->next = newNode;
      }

      list->size++;
      return 0;
   }
   return 1;
}

int insert_string_ll(LinkedList* list, char* data, int type, int index)
{
   int typeError = checkType(list, type);
   int indexToCheck = index - 1;
   if (indexToCheck < 0)
   {
      indexToCheck = 0;
   }
   int indexError = checkIndex(list, indexToCheck);
   if (!typeError && !indexError)
   {
      Node* currentPtr = list->head;
      int i = 0;
      while (currentPtr != 0 && i < index)
      {
         i++;
         if (i > 1)
         {
            currentPtr = currentPtr->next;
         }
      }

      Node* newNode = malloc(sizeof(Node));
      newNode->data = malloc(strlen(data));
      strcpy(newNode->data, data);
      newNode->next = 0;

      if (i == 0)
      {
         newNode->next = list->head;
         list->head = newNode;
      }
      else
      {
         newNode->next = currentPtr->next;
         currentPtr->next = newNode;
      }

      list->size++;
      return 0;
   }
   return 1;
}

int append_ll(LinkedList* list, void* data, int type) { return insert_ll(list, data, type, list->size); }
int append_string_ll(LinkedList* list, char* data, int type) { return insert_string_ll(list, data, type, list->size); }

int push_front_ll(LinkedList* list, void* data, int type) { return insert_ll(list, data, type, 0); }

int setAt_ll(LinkedList* list, void* data, int type, int index)
{
   int typeError = checkType(list, type);
   int indexToCheck = index - 1;
   if (indexToCheck < 0)
   {
      indexToCheck = 0;
   }
   int indexError = checkIndex(list, index);
   if (!typeError && !indexError)
   {
      Node* currentPtr = list->head;
      int i = 0;
      while (currentPtr != 0 && i < index)
      {
         i++;
         if (i > 0)
         {
            currentPtr = currentPtr->next;
         }
      }

      currentPtr->data = data;
      return 0;
   }
   return 1;
}

const void* at_ll(const LinkedList* list, int type, int index)
{
   int typeError = checkType(list, type);
   int indexToCheck = index - 1;
   if (indexToCheck < 0)
   {
      indexToCheck = 0;
   }
   int indexError = checkIndex(list, index);
   if (!typeError && !indexError)
   {
      Node* currentPtr = list->head;
      int i = 0;
      while (currentPtr != 0 && i < index)
      {
         i++;
         if (i > 0)
         {
            currentPtr = currentPtr->next;
         }
      }

      return currentPtr->data;
   }
   return NULL;
}

const void* last_ll(const LinkedList* list, int type) { return at_ll(list, type, list->size - 1); }

void printIntegerLinkedList(const LinkedList* list, const char* nameOfList)
{
   printf("==============================================\n");
   printf("Printing Linked List - %s\n", nameOfList);
   printf("==============================================\n");
   printf("Size: %d\n", list->size);
   Node* currentPtr = list->head;
   int index = 0;
   while (currentPtr != 0)
   {
      void* data = currentPtr->data;
      int* intData = (int*)data;
      printf("%s[%d] = %d\n", nameOfList, index, *intData);
      index++;
      currentPtr = currentPtr->next;
   }
}
