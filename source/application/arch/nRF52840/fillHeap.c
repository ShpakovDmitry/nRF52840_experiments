/*
 *   file: fillHeap.c
 * author: ShpakovDmitry
 *   date: 2021-01-13
 */

#include <stdint.h>

extern uint32_t __heap_start;

void fillHeap(uint32_t fillVal) {
    uint32_t *dst, *mspReg;
    dst = &__heap_start;
    __asm__("mrs %0, msp\n" : "=r" (mspReg));
    while (dst < mspReg) {
        *(dst++) = fillVal;
    }
}

