#include <nvic.h>
#include <stdint.h>

typedef volatile struct __attribute__ ((packed)) {
    uint32_t reserved0[1];  // 0x000 reserved
    uint32_t ICTR;          // 0x004 Interrupt Controller Type Register
    uint32_t reserved1[62];  // 0x008 - 0x0FC reserved
    uint32_t NVIC_ISER[8];  // 0x100 - 0x11C Interrupt Set-enable
    //TODO add remaining registers
} NvicRegisters;
