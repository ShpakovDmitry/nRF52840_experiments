#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_STRLEN 1024

size_t strlen(char* s) {
    char *p = s;
    while (*p != '\0') {
        p++;
    }
    return p - s;
}

void reverse(char s[]) {
    int i,j;
    char c;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[]) {
    int i, sign;

    if ( (sign = n) < 0 ) {
        n = -n;
    }
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ( (n/=10) > 0 );
    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}

void* memcpy(void* dst, const void* src, size_t n) {
   for (size_t i = 0; i < n; i++) {
        ((uint8_t* )dst)[i] = ((uint8_t* )src)[i];
   }
   return dst;
}
