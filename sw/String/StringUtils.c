#include "StringUtils.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void clearString(char* str)
{
   int length = strlen(str);
   for (int i = 0; i < length - 1; i++)
   {
      str[i] = '\0';
   }
}

void reverseString(char* dest, const char* src)
{
   int srcLength = strlen(src);
   int countUp = 0;
   for (int i = srcLength - 1; i >= 0; i--)
   {
      if (src[i] != '\0')
      {
         dest[countUp] = src[i];
         countUp++;
      }
   }
   dest[countUp] = '\0';
}

void lowerString(char* dest, const char* src)
{
   const char* srcItr = src;
   char* destItr = dest;
   while (*srcItr != '\0')
   {
      *destItr = tolower(*srcItr);
      destItr++;
      srcItr++;
   }
}

void removeTrailingNewLine(char* str)
{
   int size = strlen(str);
   if (str[size - 1] == '\n')
   {
      char* temp = (char*)malloc(size - 1);
      for (int i = 0; i < size - 2; i++)
      {
         temp[i] = str[i];
      }
      strncpy(str, temp, size - 1);
      free(temp);
   }
}