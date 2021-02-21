#ifndef COMMAND_LINE_OPTIONS_STRUCT_H
#define COMMAND_LINE_OPTIONS_STRUCT_H

#define NULL_COMMAND_LINE_OPTION_TEXT ""
#define NULL_COMMAND_LINE_DESCRIPTION ""
#define NULL_COMMAND_LINE_FLAG_VALUE 1

#include <stdbool.h>

struct CommandLineOption
{
    char* optionText;
    char* description;
    bool flagValue;
} typedef CommandLineOption;

#endif