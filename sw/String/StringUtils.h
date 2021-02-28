#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif  

void clearString(char* str);
void reverseString(char* dest, const char* src);
void lowerString(char* dest, const char* src);
void removeTrailingNewLine(char* str);
void removeTrailingReturnCarriage(char* str);
bool stringsAreEqual(const char* s1, const char* s2);

#ifdef __cplusplus
}
#endif  

#endif