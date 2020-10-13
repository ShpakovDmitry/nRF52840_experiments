#ifndef STRING_H
#define STRING_H

#include <stddef.h>

size_t strlen(const char* );
void swap(char* , char* );
void reverse(char str[], int length);
char* itoa(int num, char* str, int base);

#endif  // STRING_H
