/*
 *   file: Target_nRF52840.c
 * author: ShpakovDmitry
 *   date: 2020-12-18
 */

#include <Target_nRF52840.h>
#include <gpio.h>
#include <systime.h>
#include <clock.h>
#include <rtc.h>
#include <nvic.h>
#include <uart.h>

static void init();
static void puts(char* );

void nRF52840_ctor(THardware_nRF52840_Handle * me) {
    static struct THardware_nRF52840 vtable = {
        &init,
        &puts
    };

    *me = &vtable;
}
static void init() {
    Clock_setHighFreqXoDebounce(HFXO_DEBOUNCE_1024US);
    Clock_startHighFreqXo();
    SysTick_init(RELOAD_1MS_64MHZ);

    Clock_setLowFreqSource(CLOCK_LOW_FREQ_EXTERNAL);
    Clock_startLowFreqXo();

    RTC_setPrescaler(RTC_0, 32);
    RTC_startCounter(RTC_0);
    RTC_enableInterrupt(RTC_0, RTC_INT_TICK);

    //UART config
    UART_enable();
    UART_setBaudrate(UART_BAUD_115200);
    UART_disableHardwareFlowCtrl();
    UART_excludeParityBit();
    UART_setStopBits(UART_ONE_STOP_BIT);
    UART_connectPin(UART_PIN_TXD, GPIO_PORT_0, GPIO_PIN_6);
    UART_connectPin(UART_PIN_RXD, GPIO_PORT_0, GPIO_PIN_8);
    UART_initBuffers();
    UART_enableInterrupt(UART_INT_TXDRDY);
    UART_enableInterrupt(UART_INT_RXDRDY);

    NVIC_enableIrq(RTC0);
    NVIC_enableIrq(UARTE0_UART0);
    NVIC_enableGlobalIrq();
}

static void puts(char * str) {
    UART_sendString(str);
}
