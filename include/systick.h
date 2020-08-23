#ifndef SYS_TICK_H
#define SYS_TICK_H

typedef volatile struct __attribute__((packed)) {
	uint32_t reserved0[4]	/* 0x000 - 0x00C reserved*/
	uint32_t SYST_CSR;	/* 0x010 - SysTick control and status register */
	uint32_t SYST_RVR;	/* 0x014 - SysTick reload value register */
	uint32_t SYST_CVR;	/* 0x018 - SysTick current value register */
	uint32_t SYST_CALIB;	/* 0x01C - SysTick calibration value register */
} SysTickRegister;

SysTickRegister* sysTick = (SysTickRegister *)0xE000E000u;

#endif	// SYS_TICK_H
