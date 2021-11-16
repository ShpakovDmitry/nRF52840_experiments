/*
 *   file: nvic.h
 * author: ShpakovDmitry
 *   date: 2021-11-16
 */

#ifndef NVIC_H
#define NVIC_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    POWER_CLOCK                         = 0,
    RADIO                               = 1,
    UARTE0_UART0                        = 2,
    SPI0_SPIM0_SPIS0_TWI0_TWIM0_TWIS0   = 3,
    SPI1_SPIM1_SPIS1_TWI1_TWIM1_TWIS1   = 4,
    NFCT                                = 5,
    GPIOTE                              = 6,
    SAADC                               = 7,
    TIMER0                              = 8,
    TIMER1                              = 9,
    TIMER2                              = 10,
    RTC0                                = 11,
    TEMP                                = 12,
    RNG                                 = 13,
    ECB                                 = 14,
    AAR_CCM                             = 15,
    WDT                                 = 16,
    RTC1                                = 17,
    QDEC                                = 18,
    COMP_LPCOMP                         = 19,
    EGU0_SWI0                           = 20,
    EGU1_SWI1                           = 21,
    EGU2_SWI2                           = 22,
    EGU3_SWI3                           = 23,
    EGU4_SWI4                           = 24,
    EGU5_SWI5                           = 25,
    TIMER3                              = 26,
    TIMER4                              = 27,
    PWM0                                = 28,
    PDM                                 = 29,
    ACL_NVMC                            = 30,
    PPI                                 = 31,
    MWU                                 = 32,
    PWM1                                = 33,
    PWM2                                = 34,
    SPI2_SPIM2_SPIS2                    = 35,
    RTC2                                = 36,
    I2S                                 = 37,
    FPU                                 = 38,
    USBD                                = 39,
    UARTE1                              = 40,
    QSPI                                = 41,
    CC_HOST_RGF_CRYPTOCELL              = 42,
    // here is a gap
    PWM3                                = 45,
    // here is a gap
    SPIM3                               = 47
} IrqNvic;

#define MAX_PRIORITY 7
#define MIN_PRIORITY 0

#define LOWEST_PRIORITY MAX_PRIORITY
#define HIGHEST_PRIORITY MIN_PRIORITY

void NVIC_enableGlobalIrq(void);
void NVIC_disableGlobalIrq(void);

void NVIC_enableIrq(IrqNvic irqNvic);
void NVIC_disableIrq(IrqNvic irqNvic);
void NVIC_setPendingIrq(IrqNvic irqNvic);
void NVIC_clearPendingIrq(IrqNvic irqNvic);
bool NVIC_isPendingIrq(IrqNvic irqNvic);
void NVIC_setPriorityIrq(IrqNvic irqNvic, uint8_t priority);

#ifdef __cplusplus
}
#endif

#endif  // NVIC_H
