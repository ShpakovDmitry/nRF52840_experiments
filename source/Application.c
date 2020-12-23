/*
 *   file: Application.c
 * author: ShpakovDmitry
 *   date: 2020-12-18
 */

#include <Application.h>
#include <sheduler.h>
#include <Target_nRF52840.h>

static const Sheduler_Time SEND_MESSAGE_PERIOD = 1000;

void Application_run(void) {
    nRF52840_init();
    
    Sheduler_addTask(&Application_sendMessage,  SEND_MESSAGE_PERIOD);

    Sheduler_run();
}

int Application_sendMessage(void) {
    nRF52840_puts("Hello from nRF52840-DK\n");
    return 0;
}
