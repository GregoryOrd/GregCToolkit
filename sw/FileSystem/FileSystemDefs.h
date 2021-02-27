#ifndef FILE_SYSTEM_DEFS
#define FILE_SYSTEM_DEFS

#include <dirent.h>
#include <stdbool.h>

#define WINDOWS_MAX_PATH_LENGTH 260
#define DELIMITER "/"

#ifdef __cplusplus
extern "C" {
#endif

bool isVisibleDirectory(const struct dirent* fileOrSubDirectory);

#ifdef __cplusplus
}
#endif

#endif