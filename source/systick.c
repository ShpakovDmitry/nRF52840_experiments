#include <systick.h>

static volatile systime_t systime;

void SysTickHandler(void) {
	systime++;
}

systime_t getSysTime(void) {
	return systime;
}

void initSysTime(uint32_t reloadVal) {
	sysTick->SYST_RVR = reloadVal & 0x00FFFFFF;
	sysTick->SYST_CVR = 0;
	sysTick->SYST_CSR |= (1 << SYST_ENABLE);
	sysTick->SYST_CSR |= (1 << SYST_TICKINT);
}
