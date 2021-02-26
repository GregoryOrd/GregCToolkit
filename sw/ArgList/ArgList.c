#include "ArgList.h"

#include <stdlib.h>
#include <string.h>

void freeArgList(ArgList* argList)
{
   free(argList->args);
   free(argList);
}

void addStringToEndOfArgList(ArgList* list, char* buffer)
{
   list->args = realloc(list->args, ((list->size + 1) * sizeof(void*)));
   list->args[list->size] = calloc(strlen(buffer) + 1, sizeof(char));
   strcpy((char*)list->args[list->size], buffer);
   list->size++;
}

void removeLastElementFromArgList(ArgList* list)
{
   list->args = (void**)realloc(list->args, ((list->size - 1) * sizeof(void*)));
   list->size--;
}