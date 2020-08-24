#include <systime.h>

typedef volatile struct __attribute__((packed)) {
	uint32_t reserved0[4];	/* 0x000 - 0x00C reserved*/
	uint32_t SYST_CSR;	/* 0x010 - SysTick control and status register */
	uint32_t SYST_RVR;	/* 0x014 - SysTick reload value register */
	uint32_t SYST_CVR;	/* 0x018 - SysTick current value register */
	uint32_t SYST_CALIB;	/* 0x01C - SysTick calibration value register */
} SysTickRegister;

static SysTickRegister* sysTickRegister = (SysTickRegister *)0xE000E000u;

// SYST_CSR fields
#define SYST_COUNTFLAG	16
#define SYST_CLKSOURCE	2
#define SYST_TICKINT	1
#define SYST_ENABLE	0


static volatile systime_t systime;

static void disableSysTickInt(void) {
	sysTickRegister->SYST_CSR &= ~(1 << SYST_TICKINT);
}

static void enableSysTickInt(void) {
	sysTickRegister->SYST_CSR |=  (1 << SYST_TICKINT);
}

void SysTimeHandler(void) {
	disableSysTickInt();
	systime++;
	enableSysTickInt();
}

systime_t getSysTime(void) {
	return systime;
}

void initSysTime(uint32_t reloadVal) {
	sysTickRegister->SYST_RVR = reloadVal & 0x00FFFFFF;
	sysTickRegister->SYST_CVR = 0;
	sysTickRegister->SYST_CSR |= (1 << SYST_ENABLE);
	sysTickRegister->SYST_CSR |= (1 << SYST_TICKINT);
}
