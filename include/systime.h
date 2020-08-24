#ifndef SYS_TIME_H
#define SYS_TIME_H

#include <stdint.h>

typedef volatile struct __attribute__((packed)) {
	uint32_t reserved0[4];	/* 0x000 - 0x00C reserved*/
	uint32_t SYST_CSR;	/* 0x010 - SysTick control and status register */
	uint32_t SYST_RVR;	/* 0x014 - SysTick reload value register */
	uint32_t SYST_CVR;	/* 0x018 - SysTick current value register */
	uint32_t SYST_CALIB;	/* 0x01C - SysTick calibration value register */
} SysTickRegister;

SysTickRegister* sysTickRegister = (SysTickRegister *)0xE000E000u;

// SYST_CSR fields
#define SYST_COUNTFLAG	16
#define SYST_CLKSOURCE	2
#define SYST_TICKINT	1
#define SYST_ENABLE	0

typedef uint32_t systime_t;
systime_t getSysTime(void);
void initSysTime(uint32_t reloadVal);

#endif	// SYS_TIME_H
