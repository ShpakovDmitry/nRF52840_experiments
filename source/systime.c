#include <systime.h>
#include <sheduler.h>

#define SYS_TICK_BASE_ADDRESS 0xE000E000u

typedef volatile struct __attribute__((packed)) {
    uint32_t reserved0[4];  /* 0x000 - 0x00C reserved*/
    uint32_t SYST_CSR;      /* 0x010 - SysTick control and status register */
    uint32_t SYST_RVR;      /* 0x014 - SysTick reload value register */
    uint32_t SYST_CVR;      /* 0x018 - SysTick current value register */
    uint32_t SYST_CALIB;    /* 0x01C - SysTick calibration value register */
} SysTick_Register;

static SysTick_Register* sysTickRegister = (SysTick_Register *) SYS_TICK_BASE_ADDRESS;

// SYST_CSR fields
#define SYST_COUNTFLAG  16
#define SYST_CLKSOURCE  2
#define SYST_TICKINT    1
#define SYST_ENABLE     0

static volatile SysTick_time systime;
static volatile SysTick_CpuTicks cpuTicks;

#define SET_REG_BIT_LO(reg, bit) ( (sysTickRegister->reg) &= ~(1 << (bit)) )
#define SET_REG_BIT_HI(reg, bit) ( (sysTickRegister->reg) |=  (1 << (bit)) )
#define SET_REG_VAL(reg, val) ( (sysTickRegister->reg) = (val) )

static void SysTick_disableInterrupt(void) {
    SET_REG_BIT_LO(SYST_CSR, SYST_TICKINT);
}

static void SysTick_enableInterrupt(void) {
    SET_REG_BIT_HI(SYST_CSR, SYST_TICKINT);
}

__attribute__((interrupt("FIQ"))) void SysTimeHandler(void) {
    SysTick_disableInterrupt();
    systime++;
    cpuTicks += sysTickRegister->SYST_RVR;
    SysTick_enableInterrupt();
}

SysTick_time SysTick_get(void) {
    return systime;
}

void SysTick_init(uint32_t reloadVal) {
    static const uint32_t reloadMask = 0x00FFFFFF;
    static const uint32_t systcvrval = 0x00000000;
    SET_REG_VAL(SYST_RVR, reloadVal & reloadMask);
    SET_REG_VAL(SYST_CVR, systcvrval);
    SET_REG_BIT_HI(SYST_CSR, SYST_ENABLE);
    SET_REG_BIT_HI(SYST_CSR, SYST_TICKINT);
}

static uint32_t SysTick_getCurrentRegVal(void) {
    uint32_t tmp;
    tmp = sysTickRegister->SYST_CVR;
    return tmp;
}

uint64_t SysTick_getCpuTicks(void) {
    uint64_t tmp;
    SysTick_disableInterrupt();
    tmp = (uint64_t) SysTick_getCurrentRegVal();
    tmp += cpuTicks;
    SysTick_enableInterrupt();
    return tmp;
}
