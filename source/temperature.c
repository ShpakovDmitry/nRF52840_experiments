#include <temperature.h>

static const uint32_t TEMP_BASE_ADDRESS = 0x4000C000UL;

typedef volatile struct __attribute__((packed)) {
    uint32_t TASKS_START;   // 0x000 start temperature measurement 
    uint32_t TASKS_STOP;    // 0x004 stop temperature measurement
    //TODO implement remaining register map
} TEMP_Registers;

static TEMP_Registers* temp = (TEMP_Registers* )TEMP_BASE_ADDRESS;
