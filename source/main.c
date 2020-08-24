#include <stdint.h>
#include <gpio.h>
#include <systime.h>
#include <led.h>

#define BLINK_DELAY 1000

int main(void) {
	initSysTime(RELOAD_1MS_64MHZ);
	systime_t lastSysTime = getSysTime();

	initLed(LED_1);
	
	while (1) {
		if (getSysTime() - lastSysTime >= BLINK_DELAY ) {
			lastSysTime = getSysTime();
			invertLed(LED_1);
		}
	}
}
