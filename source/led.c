#include <led.h>
#include <gpio.h>

void initLed(LED led) {
	setGpioDir(GPIO_0, led, GPIO_OUTPUT);
	setLedLow(led);
}

void setLedHigh(LED led) {
	setGpioOutput(GPIO_0, led, GPIO_LOW);	/* low - because in sink mode */
}

void setLedLow(LED led) {
	setGpioOutput(GPIO_0, led, GPIO_HIGH);	/* high - because in sink mode */
}
void invertLed(LED led) {
	if ( getGpioDriver(GPIO_0, led) == GPIO_HIGH ) {
		setLedHigh(led);
	} else {
		setLedLow(led);
	}
}
