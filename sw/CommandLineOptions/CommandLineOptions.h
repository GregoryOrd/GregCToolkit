#ifndef COMMAND_LINE_OPTIONS_H
#define COMMAND_LINE_OPTIONS_H

#include "CommandLineOptionsStruct.h"
#include <stdbool.h>

typedef struct CommandLineOptionList
{
    int size;
    CommandLineOption* options;
} CommandLineOptionList;

#define NULL_COMMAND_LINE_OPTION_TEXT ""
#define NULL_COMMAND_LINE_DESCRIPTION ""
#define NULL_COMMAND_LINE_FLAG_VALUE 1

#ifdef __cplusplus
extern "C" {
#endif  

void freeCommandLineOptions(CommandLineOptionList* options);
void processCommandLineArgs(int arc, const char* argv[], CommandLineOptionList* options);
int checkForOption(const CommandLineOptionList* optionsList, const char* optionToFind);
void printSupportedOptions(const CommandLineOptionList* supportedOptions);
bool flagValueForOption(const CommandLineOptionList* optionsList, const char* optionToFind);
void addOptionIfItDoesntAlreadyExist(CommandLineOptionList* optionsList, CommandLineOption newOption);

#ifdef __cplusplus
}
#endif  

#endif