#ifndef MANAGE_DIRECTORIES_H
#define MANAGE_DIRECTORIES_H

#include <dirent.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif  

int makeDir(char* dirName);
int removeDir(char* folderName);
bool isVisibleDirectory(const struct dirent* fileOrSubDirectory);

#ifdef __cplusplus
}
#endif  

#endif