#include <led.h>
#include <gpio.h>

void LED_init(LED led) {
    GPIO_setDirection(GPIO_0, led, GPIO_OUTPUT);
    LED_setLow(led);
}

void LED_setHigh(LED led) {
    GPIO_setOutput(GPIO_0, led, GPIO_LOW);   /* low - because in sink mode */
}

void LED_setLow(LED led) {
    GPIO_setOutput(GPIO_0, led, GPIO_HIGH);  /* high - because in sink mode */
}
void LED_invert(LED led) {
    if ( GPIO_getDriver(GPIO_0, led) == GPIO_HIGH ) {
        LED_setHigh(led);
    } else {
        LED_setLow(led);
    }
}
