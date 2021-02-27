#ifndef MANAGE_DIRECTORIES_H
#define MANAGE_DIRECTORIES_H

#include <dirent.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif  

int makeDir(char* dirName);
int removeDir(char* folderName);

#ifdef __cplusplus
}
#endif  

#endif