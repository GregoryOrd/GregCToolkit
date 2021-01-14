#include "LinkedList.h"

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////
//              Private Function Prototypes                         //
//////////////////////////////////////////////////////////////////////
int checkType(LinkedList* list, int type);
int checkIndex(LinkedList* list, int index);


void main()
{
    int type = 1;
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    initEmptyLinkedList(list, type);

    int* first = (int*)malloc(sizeof(int));
    *first = 0;
    append_ll(list, first, type);
    int* second = (int*)malloc(sizeof(int));
    *second = 1;
    append_ll(list, second, type);
    int* third = (int*)malloc(sizeof(int));
    *third = 2;
    append_ll(list, third, type);
    int* fifth = (int*)malloc(sizeof(int));
    *fifth = 3;
    append_ll(list, fifth, type);
    int* fourth = (int*)malloc(sizeof(int));
    *fourth = 4;
    insert_ll(list, fourth, type, 3);
    int* sixth = (int*)malloc(sizeof(int));
    *sixth = 5;
    insert_ll(list, sixth, type, 1);
    int* seventh = (int*)malloc(sizeof(int));
    *seventh = -1;
    push_front_ll(list, seventh, type);
    int* eigth = (int*)malloc(sizeof(int));
    *eigth = -2;
    push_front_ll(list, eigth, type);   
    int* ninth = (int*)malloc(sizeof(int));
    *ninth = 425;
    append_ll(list, ninth, type);

    printIntegerLinkedList(list, "TestList");
    freeLinkedList(list);
}

//////////////////////////////////////////////////////////////////////
//              Function Implementation Section                     //
//////////////////////////////////////////////////////////////////////

int checkType(LinkedList* list, int type)
{
    if(list->dataType != type)
    {
        printf("Linked List Type Error. Can not use type: %d for Linked List of type: %d\n", 
            type, list->dataType);
        return 1;
    }
    return 0;
}

int checkIndex(LinkedList* list, int index)
{
    if(index >= list->size && list->size != 0)
    {
        printf("Linked List Index Out of Bounds. Can not access index: %d for Linked List of size: %d\n", index, list->size);
        return 1;
    }
    
    if(index < 0)
    {
        printf("Linked List Index Out of Bounds. Can not access index less than or equal to zero.\n", index, list->size);
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

void freeLinkedList(LinkedList* list)
{
    Node* itr = list->head;
    while(itr != 0)
    {
        Node* prev = itr;
        free(prev->data);
        prev->next = 0;
        free(prev);
        itr = itr->next;
    }
    list->dataType = 0;
    list->size = 0;
    free(list);
}

int size_ll(LinkedList* list, int type)
{
    int typeError = checkType(list, type);
    if(!typeError)
    {
        return list->size;
    }
    return -1;
}

int type_ll(LinkedList* list)
{
    return list->dataType;
}

int insert_ll(LinkedList* list, void* data, int type, int index)
{
    int typeError = checkType(list, type);
    int indexToCheck = index - 1;
    if(indexToCheck < 0)
    {
        indexToCheck = 0;
    }
    int indexError = checkIndex(list, indexToCheck);
    if(!typeError && !indexError)
    {
        Node* currentPtr = list->head;
        int i = 0;
        while(currentPtr != 0 && i < index)
        {
            i++;
            if(i > 1)
            {
                currentPtr = currentPtr->next;
            }
        }

        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = data;
        newNode->next = 0;

        if(i == 0)
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

int append_ll(LinkedList* list, void* data, int type)
{
    return insert_ll(list, data, type, list->size);
}

int push_front_ll(LinkedList* list, void* data, int type)
{
    return insert_ll(list, data, type, 0);
}

const void* at_ll(LinkedList* list, int type, int index){}
const void* last_ll(LinkedList* list, int type){}

void printIntegerLinkedList(LinkedList* list, const char* nameOfList)
{
    printf("==============================================\n");
    printf("Printing Linked List - %s\n", nameOfList);
    printf("==============================================\n");
    printf("Size: %d\n", list->size);
    Node* currentPtr = list->head;
    int index = 0;
    while(currentPtr != 0)
    {
        void* data = currentPtr->data;
        int* intData = (int*)data;
        printf("%s[%d] = %d\n", nameOfList, index, *intData);
        index++;
        currentPtr = currentPtr->next;
    }
}

