/*
 *   file: Target_nRF52840.h
 * author: ShpakovDmitry
 *   date: 2020-12-18
 */

#ifndef TARGET_NRF52840_H
#define TARGET_NRF52840_H

typedef enum {
    LED1 = 0, LED2, LED3, LED4,
    LED_NUM
} Leds;

void nRF52840_init(void);
void nRF52840_puts(char* );
void nRF52840_initLeds();
void nRF52840_setHighLed(Leds led);
void nRF52840_setLowLed(Leds led);
void nRF52840_invertLed(Leds led);

#endif  // TARGET_NRF52840_H
