#include "FileSystemDefs.h"

#include <stdlib.h>
#include <string.h>

bool isVisibleDirectory(const struct dirent* fileOrSubDirectory)
{
   bool dirNameStartsWithDot = strncmp(fileOrSubDirectory->d_name, ".", 1) == 0;
   bool dirNameContainsSlashDot = strstr(fileOrSubDirectory->d_name, "/.") != NULL;
   bool isHiddenDirectory = dirNameStartsWithDot || dirNameContainsSlashDot;
   return !isHiddenDirectory && fileOrSubDirectory->d_type == DT_DIR;
}