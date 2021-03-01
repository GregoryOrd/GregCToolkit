#include "FileSystemRecurser.h"

#include <stdlib.h>
#include <string.h>

#include "FileSystemDefs.h"

void recurseAndAddFilesToList(const char* basePath, ADD_TO_LIST_FUNCTION addFunction, ArgList* args)
{
   char fileOrSubDirectoryFullPath[WINDOWS_MAX_PATH_LENGTH] = "";
   struct dirent* fileOrSubDirectory;

   DIR* basePathDirectory = opendir(basePath);
   if (!basePathDirectory)
   {
      return;
   }

   while ((fileOrSubDirectory = readdir(basePathDirectory)) != NULL)
   {
      copyNameIntoPath(fileOrSubDirectoryFullPath, basePath, fileOrSubDirectory->d_name);
      addToListOrContinueRecursion(addFunction, args, basePath, fileOrSubDirectory, fileOrSubDirectoryFullPath);
   }

   closedir(basePathDirectory);
}

void copyNameIntoPath(char* path, const char* basePath, const char* fileOrSubDirectoryName)
{
   strcpy(path, basePath);
   strcat(path, DELIMITER);
   strcat(path, fileOrSubDirectoryName);
}

void addToListOrContinueRecursion(
    ADD_TO_LIST_FUNCTION addFunction, ArgList* args, const char* basePath, const struct dirent* fileOrSubDirectory, const char* fileOrSubDirectoryFullPath)
{
   bool added = addFunction(args, basePath, fileOrSubDirectory, fileOrSubDirectoryFullPath);
   if (!added && isVisibleDirectory(fileOrSubDirectory))
   {
      recurseAndAddFilesToList(fileOrSubDirectoryFullPath, addFunction, args);
   }
}