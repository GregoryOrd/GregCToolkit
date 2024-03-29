#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>

// ****************************************************************************************************//
// In an attempt to make this linked list structure generic, the data inside of the Node structure   **//
// is simply a void pointer.                                                                         **//
// Currently the mechanism for type protection is very loose. The linked list has an integer member  **//
// that the user can use to assign a type to the data of the linked list.                            **//
// Each linked list function then requires an integer argument representing this type to be passed   **//
// in to allow the execution of the function. The decision of which integer represents which data    **//
// type will be left to the user of the linked list and should be consistent through multiple uses   **//
// of the linked list in their application.                                                          **//
// ****************************************************************************************************//

typedef struct Node
{
   void* data;
   struct Node* next;
} Node;

typedef struct LinkedList
{
   int dataType;
   int size;
   Node* head;
} LinkedList;

#ifdef __cplusplus
extern "C"
{
#endif

   // This function assumes the linked list has already been allocated memory dynamically
   void initEmptyLinkedList(LinkedList* list, int type);
   // Takes care of freeing the linked list and all data inside it, even if the memory
   // was originally allocated outside of the linked list
   void freeLinkedList(LinkedList* list, void (*freeData)(void*));

   // These functions will return -1 on failure
   int size_ll(const LinkedList* list, int type);
   int type_ll(const LinkedList* list);

   // These functions will return 1 on failure, 0 on success
   // This function assumes the linked list and data have already been allocated memory dynamically
   // The only difference between insert_ll/append_ll and insert_string_ll/append_string_ll
   // is that the data is copied using strcpy rather than adjusting a pointer
   int insert_ll(LinkedList* list, void* data, int type, int index);
   int insert_string_ll(LinkedList* list, const char* data, int type, int index);
   int append_ll(LinkedList* list, void* data, int type);
   int append_string_ll(LinkedList* list, const char* data, int type);
   int append_string_voidArgs_ll(void** args);
   int push_front_ll(LinkedList* list, void* data, int type);
   int setAt_ll(LinkedList* list, void* data, int type, int index);

   // These functions will return a null pointer on failure
   const void* at_ll(const LinkedList* list, int type, int index);
   const void* last_ll(const LinkedList* list, int type);

   bool contains_ll(const LinkedList* list, const void* data, int type);
   bool contains_string_ll(const LinkedList* list, const char* data, int type);

   // Functions can be added here to print linked list for all basic types
   // For custom structs, a similar function must live outside of the toolkit
   void printIntegerLinkedList(const LinkedList* list, const char* nameOfList);

#ifdef __cplusplus
}
#endif

#endif