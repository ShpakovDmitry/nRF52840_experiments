#include <stdint.h>

#define BASE 0x5000000
#define OUTSET (*((uint32_t *) (BASE + 0x508)))
#define OUTCLR (*((uint32_t *) (BASE + 0x50C)))
#define PIN_CNF(pin) (*((uint32_t *) (BASE + 0x700 + pin * 0x4)))

#define LOOP_COUNT 1000000

int main(void) {
	unsigned int LED1 = 13;
	
	PIN_CNF(LED1) = 1;
	
	while (1) {
		OUTSET = (1 << LED1);
		for (int i = 0; i < LOOP_COUNT; i++) {
			;
		}
		OUTCLR = (1 << LED1);
		for (int i = 0; i < LOOP_COUNT; i++) {
			;
		}
	}
}

