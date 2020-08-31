#include <systime.h>
#include <sheduler.h>

typedef volatile struct __attribute__((packed)) {
    uint32_t reserved0[4];  /* 0x000 - 0x00C reserved*/
    uint32_t SYST_CSR;      /* 0x010 - SysTick control and status register */
    uint32_t SYST_RVR;      /* 0x014 - SysTick reload value register */
    uint32_t SYST_CVR;      /* 0x018 - SysTick current value register */
    uint32_t SYST_CALIB;    /* 0x01C - SysTick calibration value register */
} SysTickRegister;

static SysTickRegister* sysTickRegister = (SysTickRegister *)0xE000E000u;

// SYST_CSR fields
#define SYST_COUNTFLAG  16
#define SYST_CLKSOURCE  2
#define SYST_TICKINT    1
#define SYST_ENABLE     0


static volatile systime_t systime;

#define SET_REG_BIT_LO(reg, bit) ( (sysTickRegister->(reg)) &= ~(1 << (bit)) )
#define SET_REG_BIT_HI(reg, bit) ( (sysTickRegister->(reg)) |=  (1 << (bit)) )
#define SET_REG_VAL(reg, val) ( (sysTickRegister->(reg)) = (val) )

static void disableSysTickInt(void) {
    SET_REG_BIT_LO(SYST_CSR, SYST_TICKINT);
}

static void enableSysTickInt(void) {
    SET_REG_BIT_HI(SYST_CSR, SYST_TICKINT);
}

void SysTimeHandler(void) {
    disableSysTickInt();
    systime++;
    tickShedulerTime();
    enableSysTickInt();
}

systime_t getSysTime(void) {
    return systime;
}

void initSysTime(uint32_t reloadVal) {
    static const uint32_t reloadMask = 0x00FFFFFF;
    static const uint32_t systcvrval = 0x00000000;
    SET_REG_VAL(SYST_RVR, reloadVal & reloadMask);
    SET_REG_VAL(SYST_CVR, systcvrval);
    SET_REG_BIT_HI(SYST_CSR, SYST_ENABLE);
    SET_REG_BIT_HI(SYST_CSR, SYST_TICKINT);
}
