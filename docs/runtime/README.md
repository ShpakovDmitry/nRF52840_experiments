### Startup
Startup starts by loading four bytes from address 0x00000000 to stack pointer (SP) register and
then loading next four bytes from address 0x00000004 to program counter (PC) register which
means that first instruction that is executed after RESET is the one at this address.
So here, call to runtime routine should be called. At runtime setup we need at least copy
**.data** and **.bss** sections to RAM memory region.

### Vector table
![vector table](images/cortexM4_vector_table.png)

### C runtime
Firstly we need to define vector table. This is done by placing function address table at **.vectors**
section.
```c
__attribute__((section(".vectors")))
void (*vectors[])(void) = {
	stackTop,
	cStartup,
	dummyFn,
	dummyFn,
	dummyFn,
	dummyFn,
	dummyFn,
	dummyFn,
	dummyFn,
	dummyFn,
	dummyFn,
	dummyFn,
	dummyFn,
	dummyFn,
	dummyFn,
	dummyFn
};
```
At this moment we do not implement exception handling and ISRs. For this `dummyFn` is used. It will
hang the CPU in infinite loop:
```c
void dummyFn(void) {
	while (1) {
		;
	}
}
```
In `cStartup` we need to copy data from FLASH to RAM:
```c
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
```

---

> All information and images are taken from [NordicSemiconductors](https://infocenter.nordicsemi.com) site.
> Any copyright belongs to NordicSemiconductors©
