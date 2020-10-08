#ifndef SYS_TIME_H
#define SYS_TIME_H

#include <stdint.h>

typedef uint32_t SysTick_time;

SysTick_time SysTick_get(void);
void SysTick_init(uint32_t reloadVal);
uint32_t SysTick_getCurrentRegVal(void);

#define RELOAD_10MS_64MHZ   0x09C3FF    //  10 ms @ 64 MHZ CPU clock
#define RELOAD_1MS_64MHZ 	0x00F9FF    //   1 ms @ 64 MHZ CPU clock
#define RELOAD_100US_64MHZ	0x0018FF    // 100 us @ 64 MHZ CPU clock
#define RELOAD_10US_64MHZ	0x00027F    //  10 us @ 64 MHZ CPU clock
#define RELOAD_1US_64MHZ	0x00003F    //   1 us @ 64 MHZ CPU clock

#endif	// SYS_TIME_H
