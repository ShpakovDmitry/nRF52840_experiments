#include <stdint.h>

extern uint32_t stackTop;
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

void cStartup(void);
void dummyFn(void);

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
	&dummyFn	/* SysTick */
};

extern int main();

void cStartup(void) {
	uint32_t *src, *dst;

	src = &_etext;
	dst = &_sdata;
	while (dst < &_edata) {
		*(dst++) = *(src++);
	}

	src = &_sbss;
	while (src < &_ebss) {
		*(src++) = 0;
	}
	
	main();
	
	// if main() return then loop forever
	while (1) {
		;
	}
}

void dummyFn(void) {
	while (1) {
		;
	}
}
