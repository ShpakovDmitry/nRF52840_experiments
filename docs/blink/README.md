### Blink
To blink led1 `P0.13` should be used. Also for blink there is some sort of delay
routine is needed. For simplicity `for` loop is used.
```c
#include <stdint.h>
#include <gpio.h>

#define LOOP_COUNT 1000000

int main(void) {
	unsigned int LED1 = 13;
	
	GPIO_SET_DIR_OUT(gpio0, LED1);
	
	while (1) {
		GPIO_SET_HI(gpio0, LED1);
		for (int i = 0; i < LOOP_COUNT; i++) {
			;
		}
		GPIO_SET_LO(gpio0, LED1);
		for (int i = 0; i < LOOP_COUNT; i++) {
			;
		}
	}
}
```

---

> All information and images are taken from [NordicSemiconductors](https://infocenter.nordicsemi.com) site.
> Any copyright belongs to NordicSemiconductors©
