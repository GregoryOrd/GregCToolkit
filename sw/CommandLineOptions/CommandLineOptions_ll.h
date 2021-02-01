#ifndef COMMAND_LINE_OPTIONS_LL_H
#define COMMAND_LINE_OPTIONS_LL_H

#include "CommandLineOptionsStruct.h"
#include "../Collections/LinkedList.h"
#include <stdbool.h>

void freeCommandLineOptions_ll(LinkedList* options);
void freeCommandLineOption(void* data);
void processCommandLineArgs_ll(int arc, const char* argv[], LinkedList* options, int type);
int checkForOption_ll(const LinkedList* optionsList, char* optionToFind, int type);
void addOptionIfItDoesntAlreadyExist(LinkedList* commandLineOptions, CommandLineOption* option, int type, int index);
void printSupportedOptions_ll(const LinkedList* supportedOptions, int type);
bool flagValueForOption_ll(const LinkedList* optionsList, char* optionToFind, int type);

#endif