#include <stdint.h>

extern uint32_t stackTop;

void dummyFn(void);
void cStartup(void)			__attribute__ ((weak, alias("dummyFn")));
void NmiHandler(void)			__attribute__ ((weak, alias("dummyFn")));
void HardFaultHandler(void)		__attribute__ ((weak, alias("dummyFn")));
void MemManageFaultHandler(void)	__attribute__ ((weak, alias("dummyFn")));
void BusFaultHandler(void)		__attribute__ ((weak, alias("dummyFn")));
void UsageFaultHandler(void)		__attribute__ ((weak, alias("dummyFn")));
void SvCallHandler(void)		__attribute__ ((weak, alias("dummyFn")));
void PendSVHandler(void)		__attribute__ ((weak, alias("dummyFn")));
void SysTimeHandler(void)		__attribute__ ((weak, alias("dummyFn")));

__attribute__((section(".vectors")))
const void *vectors[] = {
	&stackTop,		/* Initial stack pointer value */
	&cStartup,		/* Reset vector */
	&NmiHandler,		/* NMI */
	&HardFaultHandler,	/* Hard fault*/
	&MemManageFaultHandler,	/* Memory management fault */
	&BusFaultHandler,	/* Bus fault */
	&UsageFaultHandler,	/* Usage fault*/
	0,			/* Reserved */
	0,			/* Reserved */
	0,			/* Reserved */
	0,			/* Reserved */
	&SvCallHandler,		/* SVCall */
	0,			/* Reserved for debug */
	0,			/* Reserved */
	&PendSVHandler,		/* PendSV */
	&SysTimeHandler		/* SysTick */
};

void dummyFn(void) {
	while (1) {
		;
	}
}
