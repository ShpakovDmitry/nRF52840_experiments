#include <systime.h>

static volatile systime_t systime;

void SysTimeHandler(void) {
	systime++;
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
