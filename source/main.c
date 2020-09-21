#include <stdint.h>
#include <gpio.h>
#include <systime.h>
#include <led.h>
#include <sheduler.h>
#include <clock.h>
#include <rtc.h>
#include <nvic.h>

#define LED_1_BLINK_PERIOD  500
#define LED_2_BLINK_PERIOD  501
#define LED_3_BLINK_PERIOD  502
#define LED_4_BLINK_PERIOD  503
int task1(void);
int task2(void);
int task3(void);
int task4(void);

int main(void) {
    Clock_setHighFreqXoDebounce(HFXO_DEBOUNCE_1024US);
    Clock_startHighFreqXo();
    initSysTime(RELOAD_1MS_64MHZ);

    Clock_setLowFreqSource(CLOCK_LOW_FREQ_EXTERNAL);
    Clock_startLowFreqXo();

    RTC_setPrescaler(RTC_0, 32);
    RTC_startCounter(RTC_0);
    RTC_enableInterrupt(RTC_0, RTC_INT_TICK);

    NVIC_enableIrq(RTC0);
    NVIC_enableGlobalIrq();

    LED_init(LED_1);
    LED_init(LED_2);
    LED_init(LED_3);
    LED_init(LED_4);

    Sheduler_addTask(&task1, LED_1_BLINK_PERIOD);
    Sheduler_addTask(&task2, LED_2_BLINK_PERIOD);
    Sheduler_addTask(&task3, LED_3_BLINK_PERIOD);
    Sheduler_addTask(&task4, LED_4_BLINK_PERIOD);

    Sheduler_run();

    return 0;
}

int task1(void) {
    LED_invert(LED_1);
    return 0;
}
int task2(void) {
    LED_invert(LED_2);
    return 0;
}
int task3(void) {
    LED_invert(LED_3);
    return 0;
}
int task4(void) {
    LED_invert(LED_4);
    return 0;
}
