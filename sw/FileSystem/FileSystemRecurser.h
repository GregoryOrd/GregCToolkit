#ifndef FILE_SYSTEM_RECURSER
#define FILE_SYSTEM_RECURSER

#include "../ArgList/ArgList.h"
#include <stdbool.h>
#include <dirent.h>

typedef bool (*ADD_TO_LIST_FUNCTION)(ArgList* args, const struct dirent* fileOrSubDirectory, const char* filePath);

#ifdef __cpluplus
extern "C" {}
#endif

void recurseAndAddFilesToList(const char* basePath, ADD_TO_LIST_FUNCTION addFunction, ArgList* args);
void copyNameIntoPath(char* path, const char* basePath, const char* fileOrSubDirectoryName);
void addToListOrContinueRecursion(ADD_TO_LIST_FUNCTION addFunction, ArgList* args, const struct dirent* fileOrSubDirectory, const char* fileOrSubDirectoryFullPath);

#ifdef __cpluplus
}
#endif

#endif