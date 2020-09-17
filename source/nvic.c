#include <nvic.h>
#include <stdint.h>

#define NVIC_BASE_ADDR 0xE000E000u

typedef volatile struct __attribute__ ((packed)) {
    uint32_t reserved0[1];      // 0x000 reserved
    uint32_t ICTR;              // 0x004 Interrupt Controller Type Register
    uint32_t reserved1[62];     // 0x008 - 0x0FC reserved
    uint32_t NVIC_ISER[8];      // 0x100 - 0x11C Interrupt Set-enable
    uint32_t reserved2[24];     // 0x120 - 0x17C reserved
    uint32_t NVIC_ICER[8];      // 0x180 - 0x19C Interrupt Clear-enable
    uint32_t reserved3[24];     // 0x1A0 - 0x1FC reserved
    uint32_t NVIC_ISPR[8];      // 0x200 - 0x21C Interrupt Set-pending
    uint32_t reserved4[24];     // 0x220 - 0x27C reserved
    uint32_t NVIC_ICPR[8];      // 0x280 - 0x29C Interrupt Clear-pending
    uint32_t reserved5[24];     // 0x2A0 - 0x2FC reserved
    uint32_t NVIC_IABR[8];      // 0x300 - 0x31C Interrupt Active-bit
    uint32_t reserved6[56];     // 0x320 - 0x3FC reserved
    uint32_t NVIC_IPR[60];      // 0x400 - 0x4EC Interrupt Priority
    uint32_t reserved7[644];    // 0x4F0 - 0xEFC reserved
    uint32_t STIR;              // 0xF00 Sortware Trigger Interrupt
} NvicRegisters;

static NvicRegisters* nvic[1] = {
    (NvicRegisters* ) NVIC_BASE_ADDR
};
