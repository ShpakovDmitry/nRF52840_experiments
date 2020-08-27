#ifndef CLOCK_H
#define CLOCK_H

typedef enum {
    HFXO_DEBOUNCE_16US = 0,
    HFXO_DEBOUNCE_32US,
    HFXO_DEBOUNCE_64US,
    HFXO_DEBOUNCE_128US,
    HFXO_DEBOUNCE_256US,
    HFXO_DEBOUNCE_512US,
    HFXO_DEBOUNCE_1024US,
    HFXO_DEBOUNCE_2048US
} HfxoDebounceTime;

void startHfxoClock(void);
void stopHfxoClock(void);
void setHfxoDebounce(HfxoDebounceTime debounceTime);

// currently external LFXO is supported
typedef enum {
    LFCLK_XTAL = 1
} LfClkSource;

void setLfClkSource(LfClkSource source);
void startLfxoClock(void);
void stopLfxoClock(void);


#endif  // CLOCK_H
