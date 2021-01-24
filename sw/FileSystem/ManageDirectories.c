#include "ManageDirectories.h"

#include <stdlib.h>

#include "../externalProgramExecution/CommandLineExecutables.h"
#include "../externalProgramExecution/ExternalProgramExecution.h"

int makeDir(char* dirName)
{
   char* const argv[] = {mkdir, dirName, "-p", NULL};
   return forkAndRunChildProcess(mkdir, argv);
}

int removeDir(char* folderName)
{
   char* const argv[] = {rm, folderName, "-r", NULL};
   return forkAndRunChildProcess(rm, argv);
}
