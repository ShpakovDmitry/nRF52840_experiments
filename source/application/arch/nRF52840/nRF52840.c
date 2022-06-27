/*
 *   file: nRF52840.c
 * author: ShpakovDmitry
 *   date: 2020-12-18
 */

#include "nRF52840.h"
#include <gpio.h>
#include <systime.h>
#include <clock.h>
#include <rtc.h>
#include <nvic.h>
#include <uart.h>
#include <spi.h>

void nRF52840_init() {
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

    // SPI config
    nRF_PinPort sckPinPort = { .port = PORT_1, .pin = PIN_15 };
    nRF_PinPort mosiPinPort = { .port = PORT_1, .pin = PIN_14 };
    nRF_PinPort misoPinPort = { .port = PORT_1, .pin = PIN_13 };

    SPI_Config spiConfig = {
        .speed = M4,
        .mode = SPI_MODE0,
        .bitOrder = MSB_FIRST,
        .sckPin = sckPinPort,
        .mosiPin = mosiPinPort,
        .misoPin = misoPinPort
    };
    SPI_configure(&spiConfig);
    SPI_enable();

    NVIC_enableIrq(RTC0);
    NVIC_enableIrq(UARTE0_UART0);
    NVIC_enableGlobalIrq();
}

void nRF52840_puts(char * str) {
    UART_sendString(str);
}


GPIO_Port LED_ports[LED_NUM] = {
    GPIO_PORT_0, /*LED1 port*/
    GPIO_PORT_0, /*LED2 port*/
    GPIO_PORT_0, /*LED3 port*/
    GPIO_PORT_0  /*LED4 port*/
};

GPIO_Pin LED_pins[LED_NUM] = {
    GPIO_PIN_13, /*LED1 pin*/
    GPIO_PIN_14, /*LED2 pin*/
    GPIO_PIN_15, /*LED3 pin*/
    GPIO_PIN_16  /*LED4 pin*/
};

void nRF52840_initLeds() {
    GPIO_setDirection(LED_ports[LED1], LED_pins[LED1], GPIO_OUTPUT);
    GPIO_setDirection(LED_ports[LED2], LED_pins[LED2], GPIO_OUTPUT);
    GPIO_setDirection(LED_ports[LED3], LED_pins[LED3], GPIO_OUTPUT);
    GPIO_setDirection(LED_ports[LED4], LED_pins[LED4], GPIO_OUTPUT);
    nRF52840_setLowLed(LED1);
    nRF52840_setLowLed(LED2);
    nRF52840_setLowLed(LED3);
    nRF52840_setLowLed(LED4);
}

void nRF52840_setHighLed(Leds led) {
    GPIO_setOutput(LED_ports[led], LED_pins[led], GPIO_LOW);
}

void nRF52840_setLowLed(Leds led) {
    GPIO_setOutput(LED_ports[led], LED_pins[led], GPIO_HIGH);
}

void nRF52840_invertLed(Leds led) {
    if ( GPIO_getDriver(LED_ports[led], LED_pins[led]) == GPIO_HIGH ) {
        nRF52840_setHighLed(led);
    } else {
        nRF52840_setLowLed(led);
    }
}
