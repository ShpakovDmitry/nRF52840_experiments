/*
 *   file: reverse.c
 * author: ShpakovDmitry
 *   date: 2021-11-16
 */

#include "string.h"

void reverse(char s[]) {
    int i,j;
    char c;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

