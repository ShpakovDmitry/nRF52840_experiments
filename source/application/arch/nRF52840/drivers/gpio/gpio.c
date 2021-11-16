/*
 *   file: gpio.c
 * author: ShpakovDmitry
 *   date: 2021-11-16
 */

#include <stdbool.h>
#include "gpio.h"

#define GPIO_PORT_0_BASE_ADDRESS 0x50000000u
#define GPIO_PORT_1_BASE_ADDRESS 0x50000300u

#define GPIO_SET_DIR_OUT(dir, bit) ( (dir->DIRSET) = (1 << (bit)) )
#define GPIO_SET_DIR_IN(dir, bit)  ( (dir->DIRCLR) = (1 << (bit)) )

#define GPIO_SET_HI(port, bit) ( (port->OUTSET) = (1 << (bit)) )
#define GPIO_SET_LO(port, bit) ( (port->OUTCLR) = (1 << (bit)) )

#define GET_GPIO_INPUT(port, bit)  ( (port->IN) &  (1 << (bit)) )
#define GET_GPIO_DRIVER(port, bit)  ( (port->OUT) &  (1 << (bit)) )

typedef volatile struct __attribute__((packed)) {
    uint32_t reserved0[321];    /* 0x000 - 0x500 reserved */
    uint32_t OUT;               /* 0x504 Write GPIO port */
    uint32_t OUTSET;            /* 0x508 Set individual bits in GPIO port */
    uint32_t OUTCLR;            /* 0x50C Clear individual bit in GPIO port */
    uint32_t IN;                /* 0x510 Read GPIO port */
    uint32_t DIR;               /* 0x514 Direction of GPIO port */
    uint32_t DIRSET;            /* 0x518 DIR set register */
    uint32_t DIRCLR;            /* 0x51C DIR clear register */
    uint32_t LATCH;             /* 0x520 Latch register */
    uint32_t DETECTMODE;        /* 0x524 Mode select */
    uint32_t reserved1[118];    /* 0x528 - 0x6FC reserved */
    uint32_t PIN_CNF[32];       /* 0x700 - 0x77C Configuration of GPIO pins*/
} GPIO_Registers;

static GPIO_Registers* gpio[2] = {
    (GPIO_Registers* ) GPIO_PORT_0_BASE_ADDRESS,
    (GPIO_Registers* ) GPIO_PORT_1_BASE_ADDRESS
};

static bool GPIO_isCorrectPortAndPin(GPIO_Port port, GPIO_Pin pin) {
    bool isCorrect = false;
    switch (port) {
        case GPIO_PORT_0:
            if (pin >= GPIO_PIN_0 && pin <= GPIO_PIN_31) {
                isCorrect = true;
            }
            break;
        case GPIO_PORT_1:
            if (pin >= GPIO_PIN_0 && pin <= GPIO_PIN_15) {
                isCorrect = true;
            }
            break;
        default:    // empty because false is default;
            break;
    }

    return isCorrect;
}

void GPIO_setDirection(GPIO_Port port, GPIO_Pin pin, GPIO_Direction direction) {
    if ( GPIO_isCorrectPortAndPin(port, pin) == false ) {
        return;
    }

    switch (direction) {
        case GPIO_INPUT:
            GPIO_SET_DIR_IN(gpio[port], pin);
            break;
        case GPIO_OUTPUT:
            GPIO_SET_DIR_OUT(gpio[port], pin);
            break;
        default:
            break;
    }
}

void GPIO_setOutput(GPIO_Port port, GPIO_Pin pin, GPIO_Output output) {
    if ( GPIO_isCorrectPortAndPin(port, pin) == false ) {
        return;
    }

    switch (output) {
    case GPIO_LOW:
        GPIO_SET_LO(gpio[port], pin);
        break;
    case GPIO_HIGH:
        GPIO_SET_HI(gpio[port], pin);
        break;
    default:
        break;
    }
}

GPIO_Output GPIO_getInput(GPIO_Port port, GPIO_Pin pin) {
    if ( GPIO_isCorrectPortAndPin(port, pin) == false ) {
        return -1;
    }

    GPIO_Output output;

    if ( GET_GPIO_INPUT(gpio[port], pin) ) {
        output = GPIO_HIGH;
    } else {
        output = GPIO_LOW;
    }

    return output;
}

GPIO_Output GPIO_getDriver(GPIO_Port port, GPIO_Pin pin) {
    if ( GPIO_isCorrectPortAndPin(port, pin) == false ) {
        return -1;
    }
    GPIO_Output output;

    if ( GET_GPIO_DRIVER(gpio[port], pin) ) {
        output = GPIO_HIGH;
    } else {
        output = GPIO_LOW;
    }

    return output;
}
