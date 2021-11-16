/*
 *   file: rtc.h
 * author: ShpakovDmitry
 *   date: 2021-11-16
 */

#ifndef RTC_H
#define RTC_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_PRESCALER_RTC 4095u
#define MAX_COMPARE_VAL 16777215u

typedef enum { RTC_0 = 0, RTC_1, RTC_2 } RTC_Module;
typedef enum { CC_0 = 0, CC_1, CC_2, CC_3} RTC_CC;
typedef enum {
    RTC_INT_TICK = 0, RTC_INT_OVRFLW,
    RTC_INT_CC0, RTC_INT_CC1, RTC_INT_CC2, RTC_INT_CC3} RTC_Interrupt;

void RTC_startCounter(RTC_Module module);
void RTC_stopCounter(RTC_Module module);
void RTC_clearCounter(RTC_Module module);
void RTC_setTrigOvrFlw(RTC_Module module);

bool RTC_isEventTick(RTC_Module module);
bool RTC_isEventOvrflw(RTC_Module module);
bool RTC_isEventCompare(RTC_Module module, RTC_CC cc);

void RTC_clearEventTick(RTC_Module module);
void RTC_clearEventOvrflw(RTC_Module module);
void RTC_clearEventCompare(RTC_Module module, RTC_CC cc);

void RTC_enableInterrupt(RTC_Module module, RTC_Interrupt interrupt);
void RTC_disableInterrupt(RTC_Module module, RTC_Interrupt interrupt);

uint32_t RTC_getCounterValue(RTC_Module module);
void RTC_setPrescaler(RTC_Module module, uint16_t prescaler);

void RTC_enableEventRouting(RTC_Module module, RTC_Interrupt interrupt);
void RTC_disableEventRouting(RTC_Module module, RTC_Interrupt interrupt);

void RTC_setCompareReg(RTC_Module module, RTC_CC cc, uint32_t value);
uint32_t RTC_getCompareReg(RTC_Module module, RTC_CC cc);

#ifdef __cplusplus
}
#endif

#endif  // RTC_H
