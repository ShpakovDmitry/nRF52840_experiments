#include <stdint.h>

extern uint32_t stackTop;

void DummyException(void);
void cStartup(void)                 __attribute__ ((weak, alias("DummyException")));
void NmiHandler(void)               __attribute__ ((weak, alias("DummyException")));
void HardFaultHandler(void)         __attribute__ ((weak, alias("DummyException")));
void MemManageFaultHandler(void)    __attribute__ ((weak, alias("DummyException")));
void BusFaultHandler(void)          __attribute__ ((weak, alias("DummyException")));
void UsageFaultHandler(void)        __attribute__ ((weak, alias("DummyException")));
void SvCallHandler(void)            __attribute__ ((weak, alias("DummyException")));
void PendSVHandler(void)            __attribute__ ((weak, alias("DummyException")));
void SysTimeHandler(void)           __attribute__ ((weak, alias("DummyException")));

__attribute__((section(".vectors")))
const void *vectors[] = {
    &stackTop,              /* Initial stack pointer value */
    &cStartup,              /* Reset vector */
    /* Exception handlers */
    &NmiHandler,            /* NMI */
    &HardFaultHandler,      /* Hard fault*/
    &MemManageFaultHandler, /* Memory management fault */
    &BusFaultHandler,       /* Bus fault */
    &UsageFaultHandler,     /* Usage fault*/
    0,                      /* Reserved */
    0,                      /* Reserved */
    0,                      /* Reserved */
    0,                      /* Reserved */
    &SvCallHandler,         /* SVCall */
    0,                      /* Reserved for debug */
    0,                      /* Reserved */
    &PendSVHandler,         /* PendSV */
    &SysTimeHandler,        /* SysTick */
    /* Interrupt handlers */
    &PowerClockHandler,     /* ID  0 Power and clock */
    &RadioHandler,          /* ID  1 Radio */
    &Uart0Handler,          /* ID  2 Uart0 and Uarte0 */
    &Spi0Twi0Handler,       /* ID  3 Spi0 and Twi0 */
    &Spi1Twi1Handler,       /* ID  4 Spi1 and Twi1 */
    &NfcTagHandler,         /* ID  5 NFC tag */
    &GpioteHandler,         /* ID  6 GPIO tasks and events */
    &SaadcHandler,          /* ID  7 Analog to digital converter */
    &Timer0Handler,         /* ID  8 Timer 0 */
    &Timer1Handler,         /* ID  9 Timer 1 */
    &Timer2Handler,         /* ID 10 Timer 2 */
    &Rtc0Handler,           /* ID 11 Real timer counter 0 */
    &TempHandler,           /* ID 12 Temperature sensor */
    &RngHandler,            /* ID 13 Random number generator */
    &EcbHandler,            /* ID 14 AES electronic code block */
    &AarCcmHandler,         /* ID 15 AAR and CCM */
    &WdtHandler,            /* ID 16 Watchdog timer */
    &Rtc1Handler,           /* ID 17 Real timer counter 1 */
    &QdecHandler,           /* ID 18 Quadrature decoder */
    &CompLpcompHandler,     /* ID 19 COMP and LPCOMP */
    &Egu0Swi0Handler,       /* ID 20 EGU0 and SWI0 */
    &Egu1Swi1Handler,       /* ID 21 EGU1 and SWI1 */
    &Egu2Swi2Handler,       /* ID 22 EGU2 and SWI2 */
    &Egu3Swi3Handler,       /* ID 23 EGU3 and SWI3 */
    &Egu4Swi4Handler,       /* ID 24 EGU4 and SWI4 */
    &Egu5Swi5Handler,       /* ID 25 EGU5 and SWI5 */
    &Timer3Handler,         /* ID 26 Timer 3 */
    &Timer4Handler,         /* ID 27 Timer 4 */
    &Pwm0Handler,           /* ID 28 Pulse Width Modulation 0 */
    &PdmHandler,            /* ID 29 Pulse Density Modulation */
    &AclNvmcHandler,        /* ID 30 ACL and NVMC */
    &PpiHandle,             /* ID 31 Programmable peripheral interconnect */
    &MvuHandle,             /* ID 32 Memory Watch Unit */
    &Pwm1Handler,           /* ID 33 Pulse Width Modulation 1 */
    &Pwm2Handler,           /* ID 34 Pulse Width Modulation 2 */
    &Spi2Handler,           /* ID 35 SPI2 */
    &Rtc2Handler,           /* ID 36 Real Timer Counter 2 */
    &I2cHandler,            /* ID 37 I2C */
    &FpuHandler,            /* ID 38 FPU */
    &UsbdHandler,           /* ID 39 USB device */
    &Uart1Handler,          /* ID 40 Uarte1 */
    &QspiHandler,           /* ID 41 QSPI */
    &CcHostRgfCryptoHandler,/* ID 42 CC_HOST_RGF and CryptoCell */
    0,                      /* ID 43 Reserved */
    0,                      /* ID 44 Reserved */
    &Pwm3Handler,           /* ID 45 PWM3 */
    0,                      /* ID 46 Reserved */
    &Spi3Handler            /* ID 47 SPI3 */
};

__attribute__((interrupt("FIQ"))) void DummyException(void) {
    while (1) {
        ;
    }
}

__attribute__((interrupt("IRQ"))) void DummyInterrupt(void) {
    while (1) {
        ;
    }
}
