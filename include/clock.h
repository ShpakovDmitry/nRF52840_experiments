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
} HighFreqDebounceTime;


typedef enum {
    CLOCK_HF,
    CLOCK_LF
} ClockType;

typedef enum {
    CLOCK_HIGH_FREQ_INTERNAL,
    CLOCK_HIGH_FREQ_EXTERNAL,
    CLOCK_LOW_FREQ_INTERNAL,
    CLOCK_LOW_FREQ_EXTERNAL,
} ClockSource;

void Clock_start(ClockType clockType);
void Clock_stop(ClockType clockType);
void Clock_setSource(ClockType clockType, ClockSource clockSource);
void Clock_setDebounce(ClockType clockType, HighFreqDebounceTime highFreqDebounceTime);


void Clock_startHighFreqXo(void);
void Clock_stopHighFreqXo(void);
void Clock_setDebounce(HfxoDebounceTime debounceTime);

// currently external LFXO is supported
typedef enum {
    LFCLK_XTAL = 1
} LfClkSource;

void Clock_setLfSource(LfClkSource source);
void Clock_startLfxoClock(void);
void Clock_stopLfxoClock(void);


#endif  // CLOCK_H
