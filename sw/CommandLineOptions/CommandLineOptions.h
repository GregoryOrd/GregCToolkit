#ifndef COMMAND_LINE_OPTIONS_H
#define COMMAND_LINE_OPTIONS_H

#include <stdbool.h>

struct CommandLineOption
{
    char* optionText;
    char* description;
    bool* flagValue;
} typedef CommandLineOption;

typedef struct CommandLineOptionList
{
    int size;
    CommandLineOption* options;
} CommandLineOptionList;

#define NULL_COMMAND_LINE_OPTION_TEXT ""
#define NULL_COMMAND_LINE_DESCRIPTION ""
#define NULL_COMMAND_LINE_FLAG_VALUE 1

void initCommandLineOptions(CommandLineOptionList* options, int size);
void freeCommandLineOptions(CommandLineOptionList* options);
void processCommandLineArgs(int arc, char* argv[], CommandLineOptionList* options);
int checkForOption(const CommandLineOptionList* optionsList, char* optionToFind);
void printSupportedOptions(const CommandLineOptionList* supportedOptions);
bool flagValueForOption(const CommandLineOptionList* optionsList, char* optionToFind);

#endif