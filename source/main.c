#include <stdint.h>
#include <gpio.h>
#include <systime.h>

#define BLINK_DELAY 1000

int main(void) {
	initSysTime(RELOAD_1MS_64MHZ);
	systime_t lastSysTime = getSysTime();
	
	unsigned int LED1 = GPIO_PIN_13;
	uint8_t led1Flag = 0;
	setGpioDir(GPIO_0, LED1, GPIO_OUTPUT);
	setGpioOutput(GPIO_0, LED1, GPIO_HIGH);
	while (1) {
		if (getSysTime() - lastSysTime >= BLINK_DELAY ) {
			lastSysTime = getSysTime();
			if (led1Flag) {
				led1Flag = 0;
				setGpioOutput(GPIO_0, LED1, GPIO_LOW);
			} else {
				led1Flag = 1;
				setGpioOutput(GPIO_0, LED1, GPIO_HIGH);
			}
		}
	}
}

