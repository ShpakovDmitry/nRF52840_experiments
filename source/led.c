#include <led.h>
#include <gpio.h>

void initLed(LED led) {
    GPIO_setDirection(GPIO_0, led, GPIO_OUTPUT);
    setLedLow(led);
}

void setLedHigh(LED led) {
    GPIO_setOutput(GPIO_0, led, GPIO_LOW);   /* low - because in sink mode */
}

void setLedLow(LED led) {
    GPIO_setOutput(GPIO_0, led, GPIO_HIGH);  /* high - because in sink mode */
}
void invertLed(LED led) {
    if ( GPIO_getDriver(GPIO_0, led) == GPIO_HIGH ) {
        setLedHigh(led);
    } else {
        setLedLow(led);
    }
}
