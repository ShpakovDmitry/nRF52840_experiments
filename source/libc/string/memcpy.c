/*
 *   file: memcpy.c
 * author: ShpakovDmitry
 *   date: 2021-11-16
 */

#include <stdint.h>
#include <stddef.h>
#include "string.h"

void* memcpy(void* dst, const void* src, size_t n) {
   for (size_t i = 0; i < n; i++) {
        ((uint8_t* )dst)[i] = ((uint8_t* )src)[i];
   }
   return dst;
}

