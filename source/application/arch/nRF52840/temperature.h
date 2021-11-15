#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <stdbool.h>
#include <stdint.h>

#define TEMP_BUFF_SIZE  100

void TEMP_startMeasure(void);
void TEMP_stopMeasure(void);
bool TEMP_isDataReady(void);
void TEMP_clearDataReady(void);
void TEMP_enableInterrupt(void);
void TEMP_disableInterrupt(void);
int32_t TEMP_getTemperature(void);

#endif  // TEMPERATURE_H
