#include <stdint.h>
#include <gpio.h>
#include <systime.h>
#include <led.h>
#include <sheduler.h>
#include <clock.h>

#define LED_1_BLINK_PERIOD  500
#define LED_2_BLINK_PERIOD  501
#define LED_3_BLINK_PERIOD  502
#define LED_4_BLINK_PERIOD  503
int task1(void);
int task2(void);
int task3(void);
int task4(void);

int main(void) {
    setHfxoDebounce(HFXO_DEBOUNCE_1024US);
    startHfxoClock();
    initSysTime(RELOAD_1MS_64MHZ);
    initLed(LED_1);
    initLed(LED_2);
    initLed(LED_3);
    initLed(LED_4);

    addTaskSheduler(&task1, LED_1_BLINK_PERIOD);
    addTaskSheduler(&task2, LED_2_BLINK_PERIOD);
    addTaskSheduler(&task3, LED_3_BLINK_PERIOD);
    addTaskSheduler(&task4, LED_4_BLINK_PERIOD);

    runSheduler();
}

int task1(void) {
    invertLed(LED_1);
    return 0;
}
int task2(void) {
    invertLed(LED_2);
    return 0;
}
int task3(void) {
    invertLed(LED_3);
    return 0;
}
int task4(void) {
    invertLed(LED_4);
    return 0;
}
