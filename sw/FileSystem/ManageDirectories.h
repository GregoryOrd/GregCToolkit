#ifndef MANAGE_DIRECTORIES_H
#define MANAGE_DIRECTORIES_H

#include <dirent.h>
#include <stdbool.h>

int makeDir(char* dirName);
int removeDir(char* folderName);
bool isVisibleDirectory(const struct dirent* fileOrSubDirectory);

#endif