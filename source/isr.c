#include <stdint.h>

void dummyFn(void);
extern uint32_t stackTop;
extern void cStartup(void);
extern void SysTimeHandler(void);


__attribute__((section(".vectors")))
const void *vectors[] = {
	&stackTop,	/* Initial stack pointer value */
	&cStartup,	/* Reset vector */
	&dummyFn,	/* NMI */
	&dummyFn,	/* Hard fault*/
	&dummyFn,	/* Memory management fault */
	&dummyFn,	/* Bus fault */
	&dummyFn,	/* Usage fault*/
	&dummyFn,	/* Reserved */
	&dummyFn,	/* Reserved */
	&dummyFn,	/* Reserved */
	&dummyFn,	/* Reserved */
	&dummyFn,	/* SVCall */
	&dummyFn,	/* Reserved for debug */
	&dummyFn,	/* Reserved */
	&dummyFn,	/* PendSV */
	&SysTimeHandler	/* SysTick */
};

void dummyFn(void) {
	while (1) {
		;
	}
}
