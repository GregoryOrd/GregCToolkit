#include "CommandLineOptions_ll.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../String/StringUtils.h"
#include "CommandLineOptionsStruct.h"

void freeCommandLineOptions_ll(LinkedList* list) { freeLinkedList(list, &freeCommandLineOption); }

void freeCommandLineOption(void* data) {}

void processCommandLineArgs_ll(int argc, const char* argv[], LinkedList* optionsList, int type)
{
   for (int i = 1; i < argc; i++)
   {
      int indexOfOptionInOptionsList = checkForOption_ll(optionsList, argv[i], type);
      if (indexOfOptionInOptionsList > -1)
      {
         CommandLineOption* option = (CommandLineOption*)at_ll(optionsList, type, indexOfOptionInOptionsList);
         option->flagValue = !option->flagValue;
      }
      else
      {
         printf("Unrecognized command line option provided: %s\n\n", argv[i]);
         printSupportedOptions_ll(optionsList, type);
         exit(1);
      }
   }
}

int checkForOption_ll(const LinkedList* optionsList, const char* optionToFind, int type)
{
   int foundIndex = -1;
   for (int i = 0; i < optionsList->size; i++)
   {
      const CommandLineOption* option = (CommandLineOption*)at_ll(optionsList, type, i);
      if (stringsAreEqual(optionToFind, option->optionText))
      {
         foundIndex = i;
      }
   }
   return foundIndex;
}

void addOptionIfItDoesntAlreadyExist(LinkedList* commandLineOptions, CommandLineOption* option, int type, int index)
{
   if (checkForOption_ll(commandLineOptions, option->optionText, type) == -1)
   {
      insert_ll(commandLineOptions, option, type, index);
   }
}

bool flagValueForOption_ll(const LinkedList* optionsList, const char* optionToFind, int type)
{
   for (int i = 0; i < optionsList->size; i++)
   {
      CommandLineOption* option = (CommandLineOption*)at_ll(optionsList, type, i);
      if (stringsAreEqual(optionToFind, option->optionText))
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