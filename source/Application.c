/*
 *   file: Application.c
 * author: ShpakovDmitry
 *   date: 2020-12-18
 */

#include <Application.h>
#include <sheduler.h>
#include <Target_nRF52840.h>
#include <led.h>

static const Sheduler_Time LED_1_BLINK_PERIOD = 500;
static const Sheduler_Time LED_2_BLINK_PERIOD = 501;
static const Sheduler_Time LED_3_BLINK_PERIOD = 502;
static const Sheduler_Time LED_4_BLINK_PERIOD = 503;
static const Sheduler_Time SEND_MESSAGE_PERIOD = 2000;

THardware_nRF52840_Handle _target;

void Application_run(void) {
    nRF52840_ctor(&_target);
    _target->init();
    LED_init(LED_1);
    LED_init(LED_2);
    LED_init(LED_3);
    LED_init(LED_4);
    
    Sheduler_addTask(&Application_blinkLed1,    LED_1_BLINK_PERIOD);
    Sheduler_addTask(&Application_blinkLed2,    LED_2_BLINK_PERIOD);
    Sheduler_addTask(&Application_blinkLed3,    LED_3_BLINK_PERIOD);
    Sheduler_addTask(&Application_blinkLed4,    LED_4_BLINK_PERIOD);
    Sheduler_addTask(&Application_sendMessage,  SEND_MESSAGE_PERIOD);

    Sheduler_run();
}

int Application_blinkLed1(void) {
    LED_invert(LED_1);
    return 0;
}
int Application_blinkLed2(void) {
    LED_invert(LED_2);
    return 0;
}
int Application_blinkLed3(void) {
    LED_invert(LED_3);
    return 0;
}
int Application_blinkLed4(void) {
    LED_invert(LED_4);
    return 0;
}

int Application_sendMessage(void) {
    //nRF52840_puts("Hello from nRF52840-DK\n");
    _target->puts("Hello from nRF52840-DK\n");
    return 0;
}
