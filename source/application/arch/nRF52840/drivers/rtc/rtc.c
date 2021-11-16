/*
 *   file: rtc.c
 * author: ShpakovDmitry
 *   date: 2021-11-16
 */

#include <stdint.h>
#include <stdbool.h>
#include <scheduler.h>
#include "nvic.h"
#include "rtc.h"

#define RTC_0_BASE_ADDRESS 0x4000B000u
#define RTC_1_BASE_ADDRESS 0x40011000u
#define RTC_2_BASE_ADDRESS 0x40024000u

typedef volatile struct __attribute__ ((packed)) {
    uint32_t TASKS_START;       // 0x000 Start RTC counter
    uint32_t TASKS_STOP;        // 0x004 Stop RTC counter
    uint32_t TASKS_CLEAR;       // 0x008 Clear RTC counter
    uint32_t TASKS_TRIGOVRFLW;  // 0x00C Set counter to 0xFFFFF0
    uint32_t reserved0[60];     // 0x010 - 0x0FC reserved
    uint32_t EVENTS_TICK;       // 0x100 Event on COUNTER increment
    uint32_t EVENTS_OVRFLW;     // 0x104 Event on COUNTER overflow
    uint32_t reserved1[14];     // 0x108 - 0x13C reserved
    uint32_t EVENTS_COMPARE[4]; // 0x140 - 0x14C Compare event on CC[n] match
    uint32_t reserved2[109];    // 0x150 - 0x300 reserved
    uint32_t INTENSET;          // 0x304 Enable interrupt
    uint32_t INTENCLR;          // 0x308 Disable interrupt
    uint32_t reserved3[13];     // 0x30C - 0x33C reserved
    uint32_t EVTEN;             // 0x340 Enable or disable event routing
    uint32_t EVTENSET;          // 0x344 Enable event routing
    uint32_t EVTENCLR;          // 0x348 Disable event routing
    uint32_t reserved4[110];    // 0x34C - 0x500 reserved
    uint32_t COUNTER;           // 0x504 Current COUNTER value
    uint32_t PRESCALER;         // 0x508 12-bit prescaler for COUNTER frequency
    uint32_t reserved5[13];     // 0x50C - 0x53C reserved
    uint32_t CC[4];             // 0x540 - 0x54C Compare register
} RTC_Registers;

static RTC_Registers* rtc[3] = {
    (RTC_Registers* ) RTC_0_BASE_ADDRESS,
    (RTC_Registers* ) RTC_1_BASE_ADDRESS,
    (RTC_Registers* ) RTC_2_BASE_ADDRESS
};

#define TASKS_START_BIT         0
#define TASKS_STOP_BIT          0
#define TASKS_CLEAR_BIT         0
#define TASKS_TRIGOVRFLW_BIT    0

#define EVENTS_TICK_BIT         0
#define EVENTS_OVRFLW_BIT       0
#define EVENTS_COMPARE_BIT      0

#define SET_BIT_HI(reg, bit) ( (reg) |=  (1 << (bit)) )
#define SET_BIT_LO(reg, bit) ( (reg) &= ~(1 << (bit)) )
#define GET_BIT(reg, bit)    ( (reg)  &  (1 << (bit)) )

static bool RTC_isCorrectModule(RTC_Module module) {
    bool isCorrect = false;
    if ( module >= RTC_0 && module <= RTC_2 ) {
        isCorrect = true;
    }
    return isCorrect;
}

static bool RTC_isCorrectCompareReg(RTC_CC CC) {
    bool isCorrect = false;
    if ( CC >= CC_0 && CC <= CC_3 ) {
        isCorrect = true;
    }
    return isCorrect;
}

static bool RTC_isCorrectInterrupt(RTC_Interrupt interrupt) {
    bool isCorrect = false;
    if ( interrupt >= RTC_INT_TICK && interrupt <= RTC_INT_CC3 ) {
        isCorrect = true;
    }
    return isCorrect;
}

static int RTC_getInterruptBit(RTC_Interrupt interrupt) {
    int val;

    switch (interrupt) {
        case RTC_INT_TICK:
            val = 0;
            break;
        case RTC_INT_OVRFLW:
            val = 1;
            break;
        case RTC_INT_CC0:
            val = 16;
            break;
        case RTC_INT_CC1:
            val = 17;
            break;
        case RTC_INT_CC2:
            val = 18;
            break;
        case RTC_INT_CC3:
            val = 19;
            break;
        default:
            val = 31;   // using this will take no effect
            break;
    }
    return val;
}

void RTC_startCounter(RTC_Module module) {
    if ( RTC_isCorrectModule(module) == false ) {
        return;
    }
    
    SET_BIT_HI(rtc[module]->TASKS_START, TASKS_START_BIT);
}

void RTC_stopCounter(RTC_Module module) {
    if ( RTC_isCorrectModule(module) == false ) {
        return;
    }
    
    SET_BIT_HI(rtc[module]->TASKS_STOP, TASKS_STOP_BIT);
}

void RTC_clearCounter(RTC_Module module) {
    if (RTC_isCorrectModule(module) == false ) {
        return;
    }

    SET_BIT_HI(rtc[module]->TASKS_CLEAR, TASKS_CLEAR_BIT);
}

void RTC_setTrigOvrFlw(RTC_Module module) {
    if (RTC_isCorrectModule(module) == false ) {
        return;
    }

    SET_BIT_HI(rtc[module]->TASKS_TRIGOVRFLW, TASKS_TRIGOVRFLW_BIT);
}

bool RTC_isEventTick(RTC_Module module) {
    if (RTC_isCorrectModule(module) == false ) {
        return false;
    }
    
    bool res = false;

    if ( GET_BIT(rtc[module]->EVENTS_TICK, EVENTS_TICK_BIT) == 1 ) {
        res = true;
    }

    return res;
}

bool RTC_isEventOvrflw(RTC_Module module) {
    if (RTC_isCorrectModule(module) == false ) {
        return false;
    }
    
    bool res = false;

    if ( GET_BIT(rtc[module]->EVENTS_OVRFLW, EVENTS_OVRFLW_BIT) == 1 ) {
        res = true;
    }

    return res;
}

bool RTC_isEventCompare(RTC_Module module, RTC_CC CC) {
    if ( RTC_isCorrectModule(module) == false) {
        return false;
    }

    if ( RTC_isCorrectCompareReg(CC) == false ) {
        return false;
    }
    
    // according to datasheet CC[3] not implemented in RTC[0]
    if (module == RTC_0 && CC == CC_3) {
        return false;
    }

    bool res = false;
    if ( GET_BIT(rtc[module]->CC[CC], EVENTS_COMPARE_BIT) == 1 ) {
        res = true;
    }
    
    return res;
}

void RTC_clearEventTick(RTC_Module module) {
    if ( RTC_isCorrectModule(module) == false ) {
        return;
    }
    
    SET_BIT_LO(rtc[module]->EVENTS_TICK, EVENTS_TICK_BIT);
}
void RTC_clearEventOvrflw(RTC_Module module) {
    if ( RTC_isCorrectModule(module) == false ) {
        return;
    }
    
    SET_BIT_LO(rtc[module]->EVENTS_OVRFLW, EVENTS_OVRFLW_BIT);
}
void RTC_clearEventCompare(RTC_Module module, RTC_CC CC) {
    if ( RTC_isCorrectModule(module) == false) {
        return;
    }

    if ( RTC_isCorrectCompareReg(CC) == false ) {
        return;
    }
    
    // according to datasheet CC[3] not implemented in RTC[0]
    if (module == RTC_0 && CC == CC_3) {
        return;
    }
    
    SET_BIT_LO(rtc[module]->CC[CC], EVENTS_COMPARE_BIT);
}

void RTC_enableInterrupt(RTC_Module module, RTC_Interrupt interrupt) {
    if ( RTC_isCorrectModule(module) == false ) {
        return;
    }

    if ( RTC_isCorrectInterrupt(interrupt) == false ) {
        return;
    }

    SET_BIT_HI(rtc[module]->INTENSET, RTC_getInterruptBit(interrupt));
}

void RTC_disableInterrupt(RTC_Module module, RTC_Interrupt interrupt) {
    if ( RTC_isCorrectModule(module) == false ) {
        return;
    }

    if ( RTC_isCorrectInterrupt(interrupt) == false ) {
        return;
    }

    SET_BIT_HI(rtc[module]->INTENCLR, RTC_getInterruptBit(interrupt));
}

uint32_t RTC_getCounterValue(RTC_Module module) {
    if ( RTC_isCorrectModule(module) == false ) {
        return 0;
    }

    return rtc[module]->COUNTER;
}

void RTC_setPrescaler(RTC_Module module, uint16_t prescaler) {
    if ( RTC_isCorrectModule(module) == false ) {
        return;
    }
    
    if ( prescaler > MAX_PRESCALER_RTC ) {
        prescaler = MAX_PRESCALER_RTC;
    }

    rtc[module]->PRESCALER = prescaler;
}

void RTC_enableEventRouting(RTC_Module module, RTC_Interrupt interrupt) {
    if ( RTC_isCorrectModule(module) == false ) {
        return;
    }

    if ( RTC_isCorrectInterrupt(interrupt) == false ) {
        return;
    }

    SET_BIT_HI(rtc[module]->EVTENSET, RTC_getInterruptBit(interrupt));
}

void RTC_disableEventRouting(RTC_Module module, RTC_Interrupt interrupt) {
    if ( RTC_isCorrectModule(module) == false ) {
        return;
    }

    if ( RTC_isCorrectInterrupt(interrupt) == false ) {
        return;
    }

    SET_BIT_HI(rtc[module]->EVTENCLR, RTC_getInterruptBit(interrupt));
}

void RTC_setCompareReg(RTC_Module module, RTC_CC CC, uint32_t value) {
    if ( RTC_isCorrectModule(module) == false ) {
        return;
    }

    if ( RTC_isCorrectCompareReg(CC) == false ) {
        return;
    }

    if ( value > MAX_COMPARE_VAL ) {
        value = MAX_COMPARE_VAL;    // saturate
    }

    rtc[module]->CC[CC] = value;
}

uint32_t RTC_getCompareReg(RTC_Module module, RTC_CC CC) {
    if ( RTC_isCorrectModule(module) == false ) {
        return 0;
    }

    if ( RTC_isCorrectCompareReg(CC) == false ) {
        return 0;
    }

    return rtc[module]->CC[CC];
}

__attribute__ ((isr)) void RTC0_Handler(void) {
    RTC_clearEventTick(RTC_0);
    Scheduler_tickTime();
}
