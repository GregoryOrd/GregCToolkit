#include "ManageDirectories.h"

#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include "../ExternalProgramExecution/CommandLineExecutables.h"
#include "../ExternalProgramExecution/ExternalProgramExecution.h"

int makeDir(char* dirName)
{
   char* const argv[] = {mkdir, dirName, "-p", NULL};
   return forkAndRunChildProcess(argv);
}

int removeDir(char* folderName)
{
   char* const argv[] = {rm, folderName, "-r", NULL};
   return forkAndRunChildProcess(argv);
}
