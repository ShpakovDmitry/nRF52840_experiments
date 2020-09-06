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
    &PowerClockHandler,     /* ID 0 Power and clock */
    &RadioHandler,          /* ID 1 Radio */
    &Uart0Handler,          /* ID 2 Uart0 and Uarte0 */
    &Spi0Twi0Handler,       /* ID 3 Spi0 and Twi0 */
    &Spi1Twi1Handler,       /* ID 4 Spi1 and Twi1 */
    &NfcTagHandler,         /* ID 5 NFC tag */
    &GpioteHandler,         /* ID 6 GPIO tasks and events */
    &SaadcHandler,          /* ID 7 Analog to digital converter */
    &Timer0Handler,         /* ID 8 Timer 0 */
    &Timer1Handler,         /* ID 9 Timer 1 */
    &Timer2Handler,         /* ID 10 Timer 2 */
    &Rtc0Handler,           /* ID 11 Real timer counter 0 */
    &TempHandler,           /* ID 12 Temperature sensor */
    &RngHandler,            /* ID 13 Random number generator */
    &EcbHandler,            /* ID 14 AES electronic code block */
    &AarCcmHandler,         /* ID 15 AAR and CCM */
    &WdtHandler,            /* ID 16 Watchdog timer */
    &Rtc1Handler,           /* ID 17 Real timer counter 1 */
    &QdecHandler,           /* ID 18 Quadrature decoder */
    &CompLpcompHandler     /* ID 19 COMP and LPCOMP */
    //TODO add remaining vectors
};

__attribute__((interrupt("FIQ"))) void DummyException(void) {
    while (1) {
        ;
    }
}
