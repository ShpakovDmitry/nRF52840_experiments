/*
 *   file: itoa.c
 * author: ShpakovDmitry
 *   date: 2021-11-16
 */

#include "string.h"

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

