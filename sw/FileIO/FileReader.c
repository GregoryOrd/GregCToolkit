#include "FileReader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../String/StringUtils.h"

int readFileWithActionAfterEachLine(const char* pathToTestFile, ArgList* argList, int (*action)(ArgList*))
{
   int error = 0;
   FILE* filePtr;
   char buffer[MAX_LINE_LENGTH] = "";
   filePtr = fopen(pathToTestFile, "r");
   if (filePtr)
   {
      while (fgets(buffer, MAX_LINE_LENGTH, (FILE*)filePtr) != NULL)
      {
         removeTrailingNewLine(buffer);
         addBufferToEndOfArgList(argList, buffer);
         error = action(argList);
         removeLastElementFromArgList(argList);
         if (error)
         {
            break;
         }
      }
   }
   else
   {
      error = 1;
   }

   fclose(filePtr);
   return error;
}

void addBufferToEndOfArgList(ArgList* list, char* buffer)
{
   list->args = (void**)realloc(list->args, ((list->size + 1) * sizeof(void*)));
   list->args[list->size] = malloc(sizeof(char*));
   strncpy((char*)list->args[list->size], buffer, strlen(buffer));
   list->size++;
}

void removeLastElementFromArgList(ArgList* list)
{
   list->args = (void**)realloc(list->args, ((list->size - 1) * sizeof(void*)));
   list->size--;
}