#ifndef ARG_LIST_H
#define ARG_LIST_H

#include <stdbool.h>

typedef struct ArgList
{
    int size;
    void** args;
} ArgList;

#ifdef __cplusplus
extern "C" {
#endif

void freeArgList(ArgList* argList, bool items);
void addStringToEndOfArgList(ArgList* list, char* buffer);
void removeLastElementFromArgList(ArgList* list);

#ifdef __cplusplus
}
#endif

#endif