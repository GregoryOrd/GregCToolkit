#include "LinkedList.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../FileSystem/FileSystemDefs.h"
#include "../../String/StringUtils.h"

//////////////////////////////////////////////////////////////////////
//              Private Function Prototypes                         //
//////////////////////////////////////////////////////////////////////
typedef Node* (*NODE_INITIALIZATION_FUNC)(void* data);

static int checkLinkedListType(const LinkedList* list, int type);
static int checkIndex(const LinkedList* list, int index);
static void initializeIfNull(LinkedList* list, int type);
static int validateListTypeAndIndex(const LinkedList* list, int type, int index);
static Node* nodeAtIndex(const LinkedList* list, int index);
static void setNextNodes(LinkedList* list, Node* newNode, Node* currentPtr, int index);
static Node* initializeNewNodeWithData(void* data);
static Node* initializeNewNodeWithString(void* data);
static int insertWithFunctionPointer(LinkedList* list, void* data, int type, int index, NODE_INITIALIZATION_FUNC initializeNode);

//////////////////////////////////////////////////////////////////////
//              Function Implementation Section                     //
//////////////////////////////////////////////////////////////////////

int checkLinkedListType(const LinkedList* list, int type)
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

void initializeIfNull(LinkedList* list, int type)
{
   bool uninitializedList = (list == NULL);
   if (uninitializedList)
   {
      list = malloc(sizeof(LinkedList));
      initEmptyLinkedList(list, type);
   }
}

int validateListTypeAndIndex(const LinkedList* list, int type, int index)
{
   int typeError = checkLinkedListType(list, type);
   int indexToCheck = index - 1;
   if (indexToCheck < 0)
   {
      indexToCheck = 0;
   }
   int indexError = checkIndex(list, indexToCheck);
   return typeError || indexError;
}

Node* nodeAtIndex(const LinkedList* list, int index)
{
   Node* currentPtr = list->head;
   int i = 0;
   while (currentPtr != 0 && i < index)
   {
      currentPtr = currentPtr->next;
      i++;
   }
   return currentPtr;
}

void setNextNodes(LinkedList* list, Node* newNode, Node* currentPtr, int index)
{
   if (index == 0)
   {
      newNode->next = list->head;
      list->head = newNode;
   }
   else
   {
      newNode->next = currentPtr->next;
      currentPtr->next = newNode;
   }
}

Node* initializeNewNodeWithData(void* data)
{
   Node* newNode = malloc(sizeof(Node));
   newNode->data = data;
   newNode->next = 0;
   return newNode;
}

Node* initializeNewNodeWithString(void* data)
{
   const char* stringData = (const char*)data;

   Node* newNode = malloc(sizeof(Node));
   newNode->data = calloc(WINDOWS_MAX_PATH_LENGTH, sizeof(char));
   strcpy(newNode->data, stringData);
   newNode->next = 0;

   return newNode;
}

int insertWithFunctionPointer(LinkedList* list, void* data, int type, int index, NODE_INITIALIZATION_FUNC initializeNode)
{
   initializeIfNull(list, type);
   int validationError = validateListTypeAndIndex(list, type, index);
   if (!validationError)
   {
      Node* currentPtr = nodeAtIndex(list, index - 1);
      Node* newNode = initializeNode(data);
      setNextNodes(list, newNode, currentPtr, index);
      list->size++;
      return 0;
   }
   return 1;
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
   int typeError = checkLinkedListType(list, type);
   if (!typeError)
   {
      return list->size;
   }
   return -1;
}

int type_ll(const LinkedList* list) { return list->dataType; }

int insert_ll(LinkedList* list, void* data, int type, int index) { return insertWithFunctionPointer(list, data, type, index, initializeNewNodeWithData); }

int insert_string_ll(LinkedList* list, const char* data, int type, int index)
{
   return insertWithFunctionPointer(list, (void*)data, type, index, initializeNewNodeWithString);
}

int append_ll(LinkedList* list, void* data, int type) { return insert_ll(list, data, type, list->size); }
int append_string_ll(LinkedList* list, const char* data, int type) { return insert_string_ll(list, data, type, list->size); }

int append_string_voidArgs_ll(void** args)
{
   LinkedList* list = (LinkedList*)args[0];
   const char* data = (const char*)args[1];
   int* type = (int*)args[2];
   return append_string_ll(list, data, *type);
}

int push_front_ll(LinkedList* list, void* data, int type) { return insert_ll(list, data, type, 0); }

int setAt_ll(LinkedList* list, void* data, int type, int index)
{
   int validationError = validateListTypeAndIndex(list, type, index);
   if (!validationError)
   {
      Node* currentPtr = nodeAtIndex(list, index);
      currentPtr->data = data;
      return 0;
   }
   return 1;
}

const void* at_ll(const LinkedList* list, int type, int index)
{
   int validationError = validateListTypeAndIndex(list, type, index);
   if (!validationError)
   {
      Node* currentPtr = nodeAtIndex(list, index);
      return currentPtr->data;
   }
   return NULL;
}

const void* last_ll(const LinkedList* list, int type) { return at_ll(list, type, list->size - 1); }

bool contains_string_ll(const LinkedList* list, char* data, int type)
{
   int typeError = checkLinkedListType(list, type);
   if (!typeError)
   {
      for (int i = 0; i < list->size; i++)
      {
         Node* node = nodeAtIndex(list, i);
         if (stringsAreEqual((char*)node->data, data))
         {
            return true;
         }
      }
   }
   return false;
}

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
