#include <stdint.h>
#include <gpio.h>
#include <systime.h>
#include <led.h>
#include <sheduler.h>
#include <clock.h>
#include <rtc.h>
#include <nvic.h>
#include <uart.h>

#define LED_1_BLINK_PERIOD  500
#define LED_2_BLINK_PERIOD  501
#define LED_3_BLINK_PERIOD  502
#define LED_4_BLINK_PERIOD  503
#define SEND_MSG_PERIOD     1000
int blinkLed1(void);
int blinkLed2(void);
int blinkLed3(void);
int blinkLed4(void);
int sendMessage(void);

void HardwareInit(void) {
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
    UART_connectPin(UART_PIN_TXD, GPIO_0, GPIO_PIN_6);
    UART_connectPin(UART_PIN_RXD, GPIO_0, GPIO_PIN_8);
    UART_initBuffers();
    UART_enableInterrupt(UART_INT_TXDRDY);

    NVIC_enableIrq(RTC0);
    NVIC_enableIrq(UARTE0_UART0);
    NVIC_enableGlobalIrq();

    LED_init(LED_1);
    LED_init(LED_2);
    LED_init(LED_3);
    LED_init(LED_4);
}

int main(void) {
    HardwareInit();

    Sheduler_addTask(&blinkLed1,    LED_1_BLINK_PERIOD);
    Sheduler_addTask(&blinkLed2,    LED_2_BLINK_PERIOD);
    Sheduler_addTask(&blinkLed3,    LED_3_BLINK_PERIOD);
    Sheduler_addTask(&blinkLed4,    LED_4_BLINK_PERIOD);
    Sheduler_addTask(&sendMessage,  SEND_MSG_PERIOD);

    Sheduler_run();

    return 0;
}

int blinkLed1(void) {
    LED_invert(LED_1);
    return 0;
}
int blinkLed2(void) {
    LED_invert(LED_2);
    return 0;
}
int blinkLed3(void) {
    LED_invert(LED_3);
    return 0;
}
int blinkLed4(void) {
    LED_invert(LED_4);
    return 0;
}

int sendMessage(void) {
    char* data = "Hello, World!\r\n";
    UART_sendData( (uint8_t* )data, 15);
    return 0;
}
