#ifndef FILE_READER_H
#define FILE_READER_H

#include "../ExternalProgramExecution/ArgListDefs.h"

#define MAX_LINE_LENGTH 255

#ifdef __cplusplus
extern "C"{
#endif

int readFileWithActionAfterEachLine(const char* pathToTestFile, ArgList* argList, int (*action)(ArgList*));
void addBufferToEndOfArgList(ArgList* list, char* buffer);
void removeLastElementFromArgList(ArgList* list);

#ifdef __cplusplus
}
#endif

#endif