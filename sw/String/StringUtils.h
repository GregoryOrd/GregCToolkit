#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif  

void clearString(char* str);
void reverseString(char* dest, const char* src);
void lowerString(char* dest, const char* src);
void removeTrailingNewLine(char* str);
void removeTrailingReturnCarriage(char* str);

#ifdef __cplusplus
}
#endif  

#endif