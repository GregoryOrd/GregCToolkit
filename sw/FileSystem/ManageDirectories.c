#include "ManageDirectories.h"

#include "../externalProgramExecution/CommandLineExecutables.h"
#include "../externalProgramExecution/ExternalProgramExecution.h"

#include <stdlib.h>

void makeDir(char* dirName)
{
    char* const argv[] = {mkdir, dirName, NULL};
    forkAndRunChildProcess(mkdir, argv);
}

void removeDir(char* folderName)
{
    char * const argv[] = {rm, folderName, "-r", NULL};
    forkAndRunChildProcess(rm, argv);  
}