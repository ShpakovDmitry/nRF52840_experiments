/*
 *   file: spi.c
 * author: ShpakovDmitry
 *   date: 2022-06-27
 */

#include <stdint.h>
#include "spi.h"

#define SPI_0_BASE_ADDRESS 0x40003000UL
#define SPI_1_BASE_ADDRESS 0x40004000UL
#define SPI_2_BASE_ADDRESS 0x40023000UL

typedef volatile struct __attribute__ ((packed)) {
    uint32_t reserved0[66];     // 0x000 - 0x104 reserved
    uint32_t EVENTS_READY;      // 0x108 TXD byte sent and RXD byte received
    uint32_t reserved1[126];    // 0x10C - 0x300 reserved
    uint32_t INTENSET;          // 0x304 Enable interrupt
    uint32_t INTENCLR;          // 0x308 Disable interrupt
    uint32_t reserved2[125];    // 0x30C - 0x4FC reserved
    uint32_t ENABLE;            // 0x500 Enable SPI
    uint32_t reserved3[1];      // 0x504 reserved
    uint32_t PSEL_SCK;          // 0x508 Pin select for SCK
    uint32_t PSEL_MOSI;         // 0x50C Pin select for MOSI
    uint32_t PSEL_MISO;         // 0x510 Pin select for MISO
    uint32_t reserved4[1];      // 0x514 reserved
    uint32_t RXD;               // 0x518 RXD register
    uint32_t TXD;               // 0x51C TXD register
    uint32_t reserved5[1];      // 0x520 reserved
    uint32_t FREQUENCY;         // 0x524 SPI frequency
    uint32_t reserved6[11];     // 0x528 - 0x550 reserved
    uint32_t CONFIG;            // 0x554 Configuration register
} SPI_Registers;

static SPI_Registers *spi[3] = {
    (SPI_Registers *) SPI_0_BASE_ADDRESS,
    (SPI_Registers *) SPI_1_BASE_ADDRESS,
    (SPI_Registers *) SPI_2_BASE_ADDRESS
};

