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
    &SysTimeHandler         /* SysTick */
};

__attribute__((interrupt("FIQ"))) void DummyException(void) {
    while (1) {
        ;
    }
}
