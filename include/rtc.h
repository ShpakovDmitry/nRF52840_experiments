#ifndef RTC_H
#define RTC_H

typedef enum { RTC_0 = 0, RTC_1, RTC_2 } RtcModule;
typedef enum { CC_0 = 0, CC_1, CC_2, CC_3} CompareReg;
typedef enum {
    INT_TICK = 0, INT_OVRFLW,
    INT_CC0, INT_CC1, INT_CC2, INT_CC3} RtcInterrupt;

void startCounterRtc(RtcModule rtcModule);
void stopCounterRtc(RtcModule rtcModule);
void clearCounterRtc(RtcModule rtcModule);
void setTrigOvrFlw(RtcModule rtcModule);

bool eventTickRtc(RtcModule rtcModule);
bool eventOvrflwRtc(RtcModule rtcModule);
bool eventCompare(RtcModule rtcModule, CompareReg compareReg);

void enableInterruptRtc(RtcModule rtcModule, RtcInterrupt rtcInterrupt);
void disableInterruptRtc(RtcModule rtcModule, RtcInterrupt rtcInterrupt);

uint32_t getCounterRtc(RtcModule rtcModule);

#endif  // RTC_H
