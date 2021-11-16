#ifndef STRING_H
#define STRING_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t strlen(const char* s);
void reverse(char s[]);
void itoa(int n, char s[]);
void* memcpy(void* dst, const void* src, size_t n);

#ifdef __cplusplus
}
#endif

#endif  // STRING_H
