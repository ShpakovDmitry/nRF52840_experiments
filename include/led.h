#ifndef LED_H
#define LED_H

#include <gpio.h>

typedef enum {
    LED_1 = GPIO_PIN_13,
    LED_2 = GPIO_PIN_14,
    LED_3 = GPIO_PIN_15,
    LED_4 = GPIO_PIN_16
} LED;

void initLed(LED led);
void setLedHigh(LED led);
void setLedLow(LED led);
void invertLed(LED led);

#endif  // LED_H
