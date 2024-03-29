/*
 *   file: strlen.c
 * author: ShpakovDmitry
 *   date: 2021-11-16
 */

#include <stddef.h>
#include "string.h"

size_t strlen(const char* s) {
    const char* p = s;
    while (*p != '\0') {
        p++;
    }
    return p - s;
}

