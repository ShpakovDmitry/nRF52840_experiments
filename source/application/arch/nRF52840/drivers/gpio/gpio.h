/*
 *   file: gpio.h
 * author: ShpakovDmitry
 *   date: 2021-11-16
 */

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { GPIO_PORT_0 = 0, GPIO_PORT_1 } GPIO_Port;
typedef enum { GPIO_INPUT = 0, GPIO_OUTPUT } GPIO_Direction;
typedef enum { GPIO_LOW = 0, GPIO_HIGH } GPIO_Output;
typedef enum {
    GPIO_PIN_0 = 0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3,
    GPIO_PIN_4,  GPIO_PIN_5,  GPIO_PIN_6,  GPIO_PIN_7,
    GPIO_PIN_8,  GPIO_PIN_9,  GPIO_PIN_10, GPIO_PIN_11,
    GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15,
    GPIO_PIN_16, GPIO_PIN_17, GPIO_PIN_18, GPIO_PIN_19,
    GPIO_PIN_20, GPIO_PIN_21, GPIO_PIN_22, GPIO_PIN_23,
    GPIO_PIN_24, GPIO_PIN_25, GPIO_PIN_26, GPIO_PIN_27,
    GPIO_PIN_28, GPIO_PIN_29, GPIO_PIN_30, GPIO_PIN_31
} GPIO_Pin;

void GPIO_setDirection(GPIO_Port port, GPIO_Pin pin, GPIO_Direction direction);
void GPIO_setOutput(GPIO_Port port, GPIO_Pin pin, GPIO_Output output);
GPIO_Output GPIO_getInput(GPIO_Port port, GPIO_Pin pin);
GPIO_Output GPIO_getDriver(GPIO_Port port, GPIO_Pin pin);

#ifdef __cplusplus
}
#endif

#endif	// GPIO_H
