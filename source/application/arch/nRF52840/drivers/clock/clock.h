/*
 *   file: clock.h
 * author: ShpakovDmitry
 *   date: 2021-11-16
 */

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
} Clock_HighFreqDebounceTime;

typedef enum {
    CLOCK_LOW_FREQ_INTERNAL = 0,
    CLOCK_LOW_FREQ_EXTERNAL = 1
} Clock_LowFreqSource;

void Clock_startHighFreqXo(void);
void Clock_stopHighFreqXo(void);
void Clock_setHighFreqXoDebounce(Clock_HighFreqDebounceTime debounceTime);

void Clock_setLowFreqSource(Clock_LowFreqSource source);
void Clock_startLowFreqXo(void);
void Clock_stopLowFreqXo(void);

#endif  // CLOCK_H
