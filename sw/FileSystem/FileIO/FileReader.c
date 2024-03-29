#include "FileReader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../String/StringUtils.h"

int readFileWithActionAfterEachLine(const char* pathToTestFile, ArgList* argList, int (*action)(ArgList*))
{
   int error = 0;
   FILE* filePtr;
   char buffer[WINDOWS_MAX_PATH_LENGTH] = "";
   filePtr = fopen(pathToTestFile, "r");
   if (filePtr)
   {
      while (fgets(buffer, WINDOWS_MAX_PATH_LENGTH, (FILE*)filePtr) != NULL)
      {
         removeTrailingNewLine(buffer);
         removeTrailingReturnCarriage(buffer);
         addStringToEndOfArgList(argList, buffer);
         error = action(argList);
         removeLastElementFromArgList(argList);
         clearString(buffer);
         if (error)
         {
            break;
         }
      }

      fclose(filePtr);
   }
   else
   {
      error = 1;
   }

   return error;
}