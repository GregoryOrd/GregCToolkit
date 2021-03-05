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
   int length = strlen(src);
   for (int i = 0; i < length; i++)
   {
      char c = src[i];
      if (c >= 'A' && c <= 'Z')
      {
         dest[i] = tolower(c);
      }
      else
      {
         dest[i] = c;
      }
   }
   dest[length] = '\0';
}

void removeTrailingNewLine(char* str)
{
   int size = strlen(str);
   if (str[size - 1] == '\n')
   {
      str[size - 1] = '\0';
   }
}

void removeTrailingReturnCarriage(char* str)
{
   int size = strlen(str);
   if (str[size - 1] == '\r')
   {
      str[size - 1] = '\0';
   }
}

bool stringsAreEqual(const char* s1, const char* s2) { return strcmp(s1, s2) == 0; }