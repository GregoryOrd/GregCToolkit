#include "CommandLineOptions_ll.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CommandLineOptionsStruct.h"

void freeCommandLineOptions_ll(LinkedList* list) { freeLinkedList(list, &freeCommandLineOption); }

void freeCommandLineOption(void* data)
{
   CommandLineOption* option = (CommandLineOption*)data;
   free(option->flagValue);
   free(option->optionText);
   free(option);
}

void processCommandLineArgs_ll(int argc, char* argv[], LinkedList* optionsList, int type)
{
   for (int i = 1; i < argc; i++)
   {
      int indexOfOptionInOptionsList = checkForOption_ll(optionsList, argv[i], type);
      if (indexOfOptionInOptionsList > -1)
      {
         CommandLineOption* option = (CommandLineOption*)at_ll(optionsList, type, indexOfOptionInOptionsList);
         bool value = option->flagValue;
         if (value) option->flagValue = !option->flagValue;
      }
      else
      {
         printf("Unrecognized command line option provided: %s\n\n", argv[i]);
         printSupportedOptions_ll(optionsList, type);
         exit(1);
      }
   }
}

int checkForOption_ll(const LinkedList* optionsList, char* optionToFind, int type)
{
   int foundIndex = -1;
   for (int i = 0; i < optionsList->size; i++)
   {
      CommandLineOption* option = (CommandLineOption*)at_ll(optionsList, type, i);
      if (strcmp(optionToFind, option->optionText) == 0)
      {
         foundIndex = i;
      }
   }
   return foundIndex;
}

bool flagValueForOption_ll(const LinkedList* optionsList, char* optionToFind, int type)
{
   for (int i = 0; i < optionsList->size; i++)
   {
      CommandLineOption* option = (CommandLineOption*)at_ll(optionsList, type, i);
      if (strcmp(optionToFind, option->optionText) == 0)
      {
         return option->flagValue;
      }
   }
   return true;
}

void printSupportedOptions_ll(const LinkedList* supportedOptions, int type)
{
   printf("Supported Options:\n");
   for (int i = 0; i < supportedOptions->size; i++)
   {
      CommandLineOption* option = (CommandLineOption*)at_ll(supportedOptions, type, i);
      printf("%s    %s\n", option->optionText, option->description);
   }
}