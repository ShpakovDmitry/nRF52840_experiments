### Startup
Startup starts by loading four bytes from address 0x00000000 to stack pointer
(SP) register and then loading next four bytes from address 0x00000004 to
program counter (PC) register which means that first instruction that is
executed after RESET is the one at this address. So here, call to runtime
routine should be called. At runtime setup we need at least copy
**.data** and **.bss** sections to RAM memory region.

### Vector table
![vector table](images/cortexM4_vector_table.png)

### C runtime
1. Firstly, we need to place stack pointer value to `.stack` section:
```c
extern uint32_t __stacktop;

__attribute__((section(".stack"), used)) uint32_t *__stack_init = &__stacktop;
```

2. Then we need to define exception vector table. This is done by placing
function address table at `.exception_vectors` section:
```c
typedef void (*funcPtr)();

void __stop(void) {
    while (1) {
        ;
    }
}

void RESET_Handler(void)        __attribute__((weak, alias("__stop")));
void NMI_Handler(void)          __attribute__((weak, alias("__stop")));
void HARDFAULT_Handler(void)    __attribute__((weak, alias("__stop")));
void MEMMANAGE_Handler(void)    __attribute__((weak, alias("__stop")));
void BUSFAULT_Handler(void)     __attribute__((weak, alias("__stop")));
void USAGEFAULT_Handler(void)   __attribute__((weak, alias("__stop")));
void SVCALL_Handler(void)       __attribute__((weak, alias("__stop")));
void PENDSV_Handler(void)       __attribute__((weak, alias("__stop")));
void SYSTICK_Handler(void)      __attribute__((weak, alias("__stop")));

void DUMMY_Handler(void)        __attribute__((weak, alias("__stop")));

__attribute__((section(".exception_vectors"), used)) funcPtr __exceptionVectors[] = {
    RESET_Handler,
    NMI_Handler,
    HARDFAULT_Handler,
    MEMMANAGE_Handler,
    BUSFAULT_Handler,
    USAGEFAULT_Handler,
    DUMMY_Handler,
    DUMMY_Handler,
    DUMMY_Handler,
    DUMMY_Handler,
    SVCALL_Handler,
    DUMMY_Handler,
    DUMMY_Handler,
    PENDSV_Handler,
    SYSTICK_Handler
};
```

3. Next, we define ISR vector table and place it to `.isr_vectors` section:
```c
void POWERCLOCK_Handler(void)        __attribute__ ((weak, alias("__stop")));
void RADIO_Handler(void)             __attribute__ ((weak, alias("__stop")));
void UART0_Handler(void)             __attribute__ ((weak, alias("__stop")));
void SPI0TWI0_Handler(void)          __attribute__ ((weak, alias("__stop")));
void SPI1TWI1_Handler(void)          __attribute__ ((weak, alias("__stop")));
void NFCTAG_Handler(void)            __attribute__ ((weak, alias("__stop")));
void GPIOTE_Handler(void)            __attribute__ ((weak, alias("__stop")));
void SAADC_Handler(void)             __attribute__ ((weak, alias("__stop")));
void TIMER0_Handler(void)            __attribute__ ((weak, alias("__stop")));
void TIMER1_Handler(void)            __attribute__ ((weak, alias("__stop")));
void TIMER2_Handler(void)            __attribute__ ((weak, alias("__stop")));
void RTC0_Handler(void)              __attribute__ ((weak, alias("__stop")));
void TEMP_Handler(void)              __attribute__ ((weak, alias("__stop")));
void RNG_Handler(void)               __attribute__ ((weak, alias("__stop")));
void ECB_Handler(void)               __attribute__ ((weak, alias("__stop")));
void AARCCM_Handler(void)            __attribute__ ((weak, alias("__stop")));
void WDT_Handler(void)               __attribute__ ((weak, alias("__stop")));
void RTC1_Handler(void)              __attribute__ ((weak, alias("__stop")));
void QDEC_Handler(void)              __attribute__ ((weak, alias("__stop")));
void COMPLPCOMP_Handler(void)        __attribute__ ((weak, alias("__stop")));
void EGU0SWI0_Handler(void)          __attribute__ ((weak, alias("__stop")));
void EGU1SWI1_Handler(void)          __attribute__ ((weak, alias("__stop")));
void EGU2SWI2_Handler(void)          __attribute__ ((weak, alias("__stop")));
void EGU3SWI3_Handler(void)          __attribute__ ((weak, alias("__stop")));
void EGU4SWI4_Handler(void)          __attribute__ ((weak, alias("__stop")));
void EGU5SWI5_Handler(void)          __attribute__ ((weak, alias("__stop")));
void TIMER3_Handler(void)            __attribute__ ((weak, alias("__stop")));
void TIMER4_Handler(void)            __attribute__ ((weak, alias("__stop")));
void PWM0_Handler(void)              __attribute__ ((weak, alias("__stop")));
void PDM_Handler(void)               __attribute__ ((weak, alias("__stop")));
void ACLNVMC_Handler(void)           __attribute__ ((weak, alias("__stop")));
void PPI_Handler(void)               __attribute__ ((weak, alias("__stop")));
void MVU_Handler(void)               __attribute__ ((weak, alias("__stop")));
void PWM1_Handler(void)              __attribute__ ((weak, alias("__stop")));
void PWM2_Handler(void)              __attribute__ ((weak, alias("__stop")));
void SPI2_Handler(void)              __attribute__ ((weak, alias("__stop")));
void RTC2_Handler(void)              __attribute__ ((weak, alias("__stop")));
void I2C_Handler(void)               __attribute__ ((weak, alias("__stop")));
void FPU_Handler(void)               __attribute__ ((weak, alias("__stop")));
void USBD_Handler(void)              __attribute__ ((weak, alias("__stop")));
void UART1_Handler(void)             __attribute__ ((weak, alias("__stop")));
void QSPI_Handler(void)              __attribute__ ((weak, alias("__stop")));
void CCHOSTRGFCRYPTO_Handler(void)   __attribute__ ((weak, alias("__stop")));
void PWM3_Handler(void)              __attribute__ ((weak, alias("__stop")));
void SPI3_Handler(void)              __attribute__ ((weak, alias("__stop")));

__attribute__((section(".isr_vectors"), used)) funcPtr __isrVectors[] = {
    POWERCLOCK_Handler,
    RADIO_Handler,
    UART0_Handler,
    SPI0TWI0_Handler,
    SPI1TWI1_Handler,
    NFCTAG_Handler,
    GPIOTE_Handler,
    SAADC_Handler,
    TIMER0_Handler,
    TIMER1_Handler,
    TIMER2_Handler,
    RTC0_Handler,
    TEMP_Handler,
    RNG_Handler,
    ECB_Handler,
    AARCCM_Handler,
    WDT_Handler,
    RTC1_Handler,
    QDEC_Handler,
    COMPLPCOMP_Handler,
    EGU0SWI0_Handler,
    EGU1SWI1_Handler,
    EGU2SWI2_Handler,
    EGU3SWI3_Handler,
    EGU4SWI4_Handler,
    EGU5SWI5_Handler,
    TIMER3_Handler,
    TIMER4_Handler,
    PWM0_Handler,
    PDM_Handler,
    ACLNVMC_Handler,
    PPI_Handler,
    MVU_Handler,
    PWM1_Handler,
    PWM2_Handler,
    SPI2_Handler,
    RTC2_Handler,
    I2C_Handler,
    FPU_Handler,
    USBD_Handler,
    UART1_Handler,
    QSPI_Handler,
    CCHOSTRGFCRYPTO_Handler,
    DUMMY_Handler,
    DUMMY_Handler,
    PWM3_Handler,
    DUMMY_Handler,
    SPI3_Handler
};
```

Thats it. If need to define custom exception or isr vector handler, simply
define it in any translation unit as global(do not use `static` keyword).

If not defined exception or isr is called than default handler is called:
```c
void __stop(void);
```
Which puts microcontroller into infinite loop;

4. After sections are defined we need to copy `.data` section in `RAM`:
```c
void copyDataSection(void) {
    uint32_t *src, *dst;
    src = &__data_load;
    dst = &__data_start;
    while (dst < &__data_end) {
        *(dst++) = *(src++);
    }
}
```

5. Initialize `.bss` section in `RAM` with zeros:
```c
void copyBssSection(void) {
    uint32_t *src;
    src = &__bss_start;
    while (src < &__bss_end) {
        *(src++) = 0;
    }
}
```

6. Fill heap with some value(not mandatory):
```c
void fillHeap(uint32_t fillVal) {
    uint32_t *dst, *mspReg;
    dst = &__heap_start;
    __asm__("mrs %0, msp\n" : "=r" (mspReg));
    while (dst < mspReg) {
        *(dst++) = fillVal;
    }
}
```

7. Call constructors:
```c
void callInitArray(void) {
    funcPtr* array = __preinit_array_start;
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
```

8. Call `main()`.

9. If `main()` returns then call destructors:
```c
void callFiniArray(void) {
    funcPtr* array = __fini_array_start;
    while (array < __fini_array_end) {
        (*array)();
        array++;
    }
}
```

10. All this is done inside `RESET` exception handler:
```c
void RESET_Handler() {
    copyDataSection();
    copyBssSection();
    fillHeap(0xDEADC0DE);
    callInitArray();
    main();
    callFiniArray();
    while (1) {
        ;
    }
}
```

---

> All images are taken from [ARM](https://www.arm.com/) site.
