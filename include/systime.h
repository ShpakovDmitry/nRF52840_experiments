#ifndef SYS_TIME_H
#define SYS_TIME_H

#include <stdint.h>

typedef uint32_t systime_t;

systime_t getSysTime(void);
void initSysTime(uint32_t reloadVal);

#endif	// SYS_TIME_H
