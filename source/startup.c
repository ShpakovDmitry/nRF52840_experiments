/*
 *   file: startup.c
 * author: ShpakovDmitry
 *   date: 2020-08-20
 */

#include <stdint>

typedef void (*funcPtr)();

extern uint32_t __data_start;
extern uint32_t __data_end;
extern uint32_t __data_load;
extern uint32_t __bss_start;
extern uint32_t __bss_end;
extern uint32_t __heap_start;

extern void main(void);

extern funcPtr __preinit_array_start[];
extern funcPtr __preinit_array_end[];
extern funcPtr __init_array_start[];
extern funcPtr __init_array_end[];
extern funcPtr __fini_array_start[];
extern funcPtr __fini_array_end[];

void copyDataSection(void) {
    uint32_t *src, *dst;
    src = &__data_load;
    dst = &__data_start;
    while (dst < &__data_end) {
        *(dst++) = *(src++);
    }
}

void copyBssSection(void) {
    uint32_t *src;
    src = &__bss_start;
    while (src < &__bss_end) {
        *(src++) = 0;
    }
}

void fillHeap(uint32_t fillVal) {
    uint32_t *dst, *mspReg;
    dst = &__heap_start;
    __asm__("mrs %0, msp\n" : "=r" (mspReg));
    while (dst < mspReg) {
        *(dst++) = fillVal;
    }
}

void callInitArray(void) {
    auto array = __preinit_array_start;
    while (array < __preinit_array_end) {
        (*array)();
        array++;
    }
    array = __init_array_start;
    while (array < __init_array_end) {
        (*array)();
        array++;
    }
}

void callFiniArray(void) {
    auto array = __fini_array_start;
    while (array < __fini_array_end) {
        (*array)();
        array++;
    }
}

void RESET_Handler() {
    copyDataSection();
    copyBssSection();
    fillHeap(0xDEADC0DE);
    callInitArray();
    main();
    callFiniArray();
    while (true) {
        ;
    }
}
