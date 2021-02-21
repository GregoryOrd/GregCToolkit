#include "ManageDirectories.h"

#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include "../externalProgramExecution/CommandLineExecutables.h"
#include "../externalProgramExecution/ExternalProgramExecution.h"

int makeDir(char* dirName)
{
   char* const argv[] = {mkdir, dirName, "-p", NULL};
   return popenChildProcess(mkdir, 4, argv);
}

int removeDir(char* folderName)
{
   char* const argv[] = {rm, folderName, "-r", NULL};
   return popenChildProcess(rm, 4, argv);
}

bool isVisibleDirectory(const struct dirent* fileOrSubDirectory)
{
   bool dirNameStartsWithDot = strncmp(fileOrSubDirectory->d_name, ".", 1) == 0;
   bool dirNameContainsSlashDot = strstr(fileOrSubDirectory->d_name, "/.") != NULL;
   bool isHiddenDirectory = dirNameStartsWithDot || dirNameContainsSlashDot;
   return !isHiddenDirectory && fileOrSubDirectory->d_type == DT_DIR;
}