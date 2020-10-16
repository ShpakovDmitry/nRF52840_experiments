#ifndef STRING_H
#define STRING_H

#include <stddef.h>

size_t strlen(char* s);
void reverse(char s[]);
void itoa(int n, char s[]);
void* memcpy(void* dst, const void* src, size_t n);

#endif  // STRING_H
