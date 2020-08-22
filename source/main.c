#include <stdint.h>
#include <gpio.h>

#define LOOP_COUNT 1000000

int main(void) {
	unsigned int LED1 = 13;

	gpio1->PIN_CNF[LED1] = 1;
	
	while (1) {
		gpio1->OUTSET = 1 << LED1;
		for (int i = 0; i < LOOP_COUNT; i++) {
			;
		}
		gpio1->OUTCLR = 1 << LED1;
		for (int i = 0; i < LOOP_COUNT; i++) {
			;
		}
	}
}

