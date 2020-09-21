#ifndef LED_H
#define LED_H

#include <gpio.h>

typedef enum {
    LED_1 = GPIO_PIN_13,
    LED_2 = GPIO_PIN_14,
    LED_3 = GPIO_PIN_15,
    LED_4 = GPIO_PIN_16
} LED;

void LED_init(LED led);
void LED_setHigh(LED led);
void LED_setLow(LED led);
void LED_invert(LED led);

#endif  // LED_H
