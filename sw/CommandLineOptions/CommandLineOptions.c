#include "CommandLineOptions.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../String/StringUtils.h"

void freeCommandLineOptions(CommandLineOptionList* list)
{
   free(list->options);
   free(list);
}

void processCommandLineArgs(int argc, const char* argv[], CommandLineOptionList* optionsList)
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

void addOptionIfItDoesntAlreadyExist(CommandLineOptionList* optionsList, CommandLineOption newOption)
{
   if (checkForOption(optionsList, newOption.optionText) == -1)
   {
      optionsList->options = realloc(optionsList->options, (optionsList->size + 1) * sizeof(CommandLineOption));
      strcpy(optionsList->options[optionsList->size].description, newOption.description);
      strcpy(optionsList->options[optionsList->size].optionText, newOption.optionText);
      optionsList->options[optionsList->size].flagValue = newOption.flagValue;
      optionsList->size++;
   }
}