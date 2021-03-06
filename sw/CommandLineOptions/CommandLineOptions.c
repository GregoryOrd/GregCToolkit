#include "CommandLineOptions.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../String/StringUtils.h"

void initCommandLineOptions(CommandLineOptionList* list, int size)
{
   list->size = size;
   list->options = malloc(size * sizeof(CommandLineOption));

   for (int i = 0; i < size; i++)
   {
      strcpy(list->options[i].description, NULL_COMMAND_LINE_DESCRIPTION);
      strcpy(list->options[i].optionText, NULL_COMMAND_LINE_OPTION_TEXT);
      list->options[i].flagValue = NULL_COMMAND_LINE_FLAG_VALUE;
   }
}

void freeCommandLineOptions(CommandLineOptionList* list)
{
   for (int i = 0; i < list->size; i++)
   {
      free(&list->options[i]);
   }
   free(list);
}

void processCommandLineArgs(int argc, char* argv[], CommandLineOptionList* optionsList)
{
   for (int i = 1; i < argc; i++)
   {
      int indexOfOptionInOptionsList = checkForOption(optionsList, argv[i]);
      if (indexOfOptionInOptionsList > -1)
      {
         optionsList->options[indexOfOptionInOptionsList].flagValue = !optionsList->options[indexOfOptionInOptionsList].flagValue;
      }
      else
      {
         printf("Unrecognized command line option provided: %s\n\n", argv[i]);
         printSupportedOptions(optionsList);
         exit(1);
      }
   }
}

int checkForOption(const CommandLineOptionList* optionsList, const char* optionToFind)
{
   int foundIndex = -1;
   for (int i = 0; i < optionsList->size; i++)
   {
      if (stringsAreEqual(optionToFind, optionsList->options[i].optionText))
      {
         foundIndex = i;
      }
   }
   return foundIndex;
}

bool flagValueForOption(const CommandLineOptionList* optionsList, const char* optionToFind)
{
   for (int i = 0; i < optionsList->size; i++)
   {
      if (stringsAreEqual(optionToFind, optionsList->options[i].optionText))
      {
         return optionsList->options[i].flagValue;
      }
   }
   return true;
}

void printSupportedOptions(const CommandLineOptionList* supportedOptions)
{
   printf("Supported Options:\n");
   for (int optionNum = 0; optionNum < supportedOptions->size; optionNum++)
   {
      printf("%s    %s\n", supportedOptions->options[optionNum].optionText, supportedOptions->options[optionNum].description);
   }
}