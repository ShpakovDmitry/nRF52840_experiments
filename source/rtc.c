#include <stdint.h>
#include <stdbool.h>
#include <rtc.h>

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
} RtcRegisters;

static RtcRegisters* rtc[3] = {
    (RtcRegisters* )0x4000B000,
    (RtcRegisters* )0x40011000,
    (RtcRegisters* )0x40024000
};

#define TASKS_START_BIT         0
#define TASKS_STOP_BIT          0
#define TASKS_TRIGOVRFLW_BIT    0

#define EVENTS_TICK_BIT         0

#define SET_BIT_HI(reg, bit) ( (reg) |=  (1 << (bit)) )
#define SET_BIT_LO(reg, bit) ( (reg) &= ~(1 << (bit)) )
#define GET_BIT(reg, bit)    ( (reg)  &  (1 << (bit)) )

static bool isCorrectModuleRtc(RtcModule rtcModule) {
    bool isCorrect = false;
    if ( rtcModule >= RTC_0 && rtcModule <= RTC_2 ) {
        isCorrect = true;
    }
    return isCorrect;
}

void startCounterRtc(RtcModule rtcModule) {
    if ( isCorrectModuleRtc(rtcModule) == false ) {
        return;
    }
    
    SET_BIT_HI(rtc[rtcModule]->TASKS_START, TASKS_START_BIT);
}

void stopCounterRtc(RtcModule rtcModule) {
    if ( isCorrectModuleRtc(rtcModule) == false ) {
        return;
    }
    
    SET_BIT_HI(rtc[rtcModule]->TASKS_STOP, TASKS_STOP_BIT);
}

void clearCounterRtc(RtcModule rtcModule) {
    if (isCorrectModuleRtc(rtcModule) == false ) {
        return;
    }

    SET_BIT_HI(rtc[rtcModule]->TASKS_CLEAR, TASKS_CLEAR_BIT);
}

void setTrigOvrFlw(RtcModule rtcModule) {
    if (isCorrectModuleRtc(rtcModule) == false ) {
        return;
    }

    SET_BIT_HI(rtc[rtcModule]->TASKS_TRIGOVRFLW, TASKS_TRIGOVRFLW_BIT);
}

bool eventTickRtc(RtcModule rtcModule) {
    if (isCorrectModuleRtc(rtcModule) == false ) {
        return false;
    }
    
    bool res = false;

    if ( GET_BIT(rtc[rtcModule]->EVENTS_TICK, EVENTS_TICK_BIT) == 1 ) {
        res = true;
    }

    return res;
}
