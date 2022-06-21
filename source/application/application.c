/*
 *   file: application.c
 * author: ShpakovDmitry
 *   date: 2020-12-18
 */

#include <stdbool.h>
#include <scheduler.h>
#include <nRF52840.h>
#include <spim0.h>
#include "application.h"


void Application_run(void) {
    Application_initHardware();
    Application_initScheduler();
    Application_runScheduler();
    // should never get here
    Application_halt();
}

#define SIZE 64

uint8_t rxBuff[SIZE] = {0x55};
uint8_t txBuff[SIZE] = {0xAA};

void Application_initHardware(void) {
    nRF52840_init();
    SPIM0_Config config;
    config.speed = K125;
    config.mode = SPI_MODE0;
    config.bitOrder = LSB_FIRST;
    config.sckPort = PORT_0;
    config.sckPin = PIN_19;
    config.mosiPort = PORT_0;
    config.mosiPin = PIN_21;
    config.misoPort = PORT_0;
    config.misoPin = PIN_23;
    config.csnPort = PORT_0;
    config.csnPin = PIN_25;
    SPIM0_configure(&config);
    SPIM0_setTransmitBuffer(txBuff, SIZE);
    SPIM0_setReceiveBuffer(rxBuff,  SIZE);
    SPIM0_enable();
    nRF52840_initLeds();
}

void Application_initScheduler(void) {
    const Scheduler_Time SEND_MESSAGE_PERIOD = 1000;
    const Scheduler_Time LED1_BLINK_PERIOD = 500;
    const Scheduler_Time LED2_BLINK_PERIOD = 501;
    const Scheduler_Time LED3_BLINK_PERIOD = 502;
    const Scheduler_Time LED4_BLINK_PERIOD = 503;

    Scheduler_addTask(&Application_sendMessage,  SEND_MESSAGE_PERIOD);
    Scheduler_addTask(&Application_blinkLed1,  LED1_BLINK_PERIOD);
    Scheduler_addTask(&Application_blinkLed2,  LED2_BLINK_PERIOD);
    Scheduler_addTask(&Application_blinkLed3,  LED3_BLINK_PERIOD);
    Scheduler_addTask(&Application_blinkLed4,  LED4_BLINK_PERIOD);
}

void Application_runScheduler(void) {
    Scheduler_run();
}

void Application_halt() {
    while (true) { ; }
}

int Application_sendMessage(void) {
    nRF52840_puts("Hello from nRF52840-DK\n");
    return 0;
}

int Application_blinkLed1(void) {
    nRF52840_invertLed(LED1);
    SPIM0_transfer();
    return 0;
}

int Application_blinkLed2(void) {
    nRF52840_invertLed(LED2);
    return 0;
}

int Application_blinkLed3(void) {
    nRF52840_invertLed(LED3);
    return 0;
}

int Application_blinkLed4(void) {
    nRF52840_invertLed(LED4);
    return 0;
}

