#ifndef CLOCK_H
#define CLOCK_H

typedef enum {
	HFXO_DEBOUNCE_256US = 0x10,
	HFXO_DEBOUNCE_1024US = 0x40
} HfxoDebounceTime;

void startHfxoClock(void);
void stopHfxoClock(void);
void setHfxoDebounce(HfxoDebounceTime debounceTime);

#endif	// CLOCK_H
