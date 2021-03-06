#include "ArgList.h"

#include <stdlib.h>
#include <string.h>

#include "../FileSystem/FileSystemDefs.h"

void freeArgList(ArgList* argList, bool items)
{
   if (items && argList->args != NULL)
   {
      for (int i = 0; i < argList->size; i++)
      {
         if (argList->args[i] != NULL)
         {
            free(argList->args[i]);
         }
      }
   }
   free(argList->args);
   free(argList);
}

void addStringToEndOfArgList(ArgList* list, char* buffer)
{
   list->args = realloc(list->args, ((list->size + 1) * sizeof(void*)));
   list->args[list->size] = calloc(WINDOWS_MAX_PATH_LENGTH, sizeof(char));
   strcpy((char*)list->args[list->size], buffer);
   list->size++;
}

void removeLastElementFromArgList(ArgList* list)
{
   void* last = list->args[list->size - 1];
   list->args = (void**)realloc(list->args, ((list->size - 1) * sizeof(void*)));
   list->size--;
   free(last);
}