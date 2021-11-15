#include <stdint.h>
#include "temperature.h"

static const uint32_t TEMP_BASE_ADDRESS = 0x4000C000UL;

typedef volatile struct __attribute__((packed)) {
    uint32_t TASKS_START;       // 0x000 start temperature measurement 
    uint32_t TASKS_STOP;        // 0x004 stop temperature measurement
    uint32_t reserved0[62];     // 0x008 - 0x0FC reserved
    uint32_t EVENTS_DATARDY;    // 0x100 temperarure measurement complete
    uint32_t reserved1[128];    // 0x104 - 0x300 reserved
    uint32_t INTENSET;          // 0x304 enable interrupt
    uint32_t INTENCLR;          // 0x308 disable interrupt
    uint32_t reserved2[127];    // 0x30C - 0x504 reserved
    uint32_t TEMP;              // 0x508 temperature in C (0.25 deg steps)
    uint32_t reserved3[5];      // 0x50C - 0x51C reserved
    uint32_t A0;                // 0x520 slope of 1st piece wise linear func
    uint32_t A1;                // 0x524 slope of 2st piece wise linear func
    uint32_t A2;                // 0x528 slope of 3st piece wise linear func
    uint32_t A3;                // 0x52C slope of 4st piece wise linear func
    uint32_t A4;                // 0x530 slope of 5st piece wise linear func
    uint32_t A5;                // 0x524 slope of 6st piece wise linear func
    uint32_t reserved4[6];      // 0x528 - 0x53C reserved
    uint32_t B0;                // 0x540 y-intercept of 1 piece wise lin func
    uint32_t B1;                // 0x544 y-intercept of 2 piece wise lin func
    uint32_t B2;                // 0x548 y-intercept of 3 piece wise lin func
    uint32_t B3;                // 0x54C y-intercept of 4 piece wise lin func
    uint32_t B4;                // 0x550 y-intercept of 5 piece wise lin func
    uint32_t B5;                // 0x554 y-intercept of 6 piece wise lin func
    uint32_t reserved5[2];      // 0x558 - 0x55C reserved
    uint32_t T0;                // 0x560 end point of 1 piece wise lin func
    uint32_t T1;                // 0x564 end point of 2 piece wise lin func
    uint32_t T2;                // 0x568 end point of 3 piece wise lin func
    uint32_t T3;                // 0x56C end point of 4 piece wise lin func
    uint32_t T4;                // 0x570 end point of 5 piece wise lin func
} TEMP_Registers;

static TEMP_Registers* temp = (TEMP_Registers* )TEMP_BASE_ADDRESS;

#define TASKS_START_BIT     0
#define TASKS_STOP_BIT      0
#define EVENTS_DATARDY_BIT  0
#define INT_DATARDY_BIT     0

#define SET_BIT_HI(reg, bit) ( (reg) |=  (1 << (bit)) )
#define SET_BIT_LO(reg, bit) ( (reg) &= ~(1 << (bit)) )
#define GET_BIT(reg, bit)    ( (reg)  &  (1 << (bit)) )

void TEMP_startMeasure(void) {
    SET_BIT_HI(temp->TASKS_START, TASKS_START_BIT);
}

void TEMP_stopMeasure(void) {
    SET_BIT_HI(temp->TASKS_STOP, TASKS_STOP_BIT);
}

bool TEMP_isDataReady(void) {
    bool res = false;
    if ( GET_BIT(temp->EVENTS_DATARDY, EVENTS_DATARDY_BIT) ) {
        res = true;
    }
    return res;
}

void TEMP_clearDataReady(void) {
    SET_BIT_LO(temp->EVENTS_DATARDY, EVENTS_DATARDY_BIT);
}

void TEMP_enableInterrupt(void) {
    SET_BIT_HI(temp->INTENSET, INT_DATARDY_BIT);
}

void TEMP_disableInterrupt(void) {
    SET_BIT_HI(temp->INTENCLR, INT_DATARDY_BIT);
}

int32_t TEMP_getTemperature(void) {
    return temp->TEMP;
}

__attribute__((isr)) void TEMP_Handler(void) {
    TEMP_clearDataReady();
    // place interrupt handler here
}
