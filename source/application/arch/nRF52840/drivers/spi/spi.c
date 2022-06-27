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

#define SET_BIT_HI(reg, bit) ( (reg) |=  (1 << (bit)) )
#define SET_BIT_LO(reg, bit) ( (reg) &= ~(1 << (bit)) )

#define ENABLE_BIT (0)

void SPI_enable() {
    SET_BIT_HI(spi[0]->ENABLE, ENABLE_BIT);
}

void SPI_disable() {
    SET_BIT_LO(spi[0]->ENABLE, ENABLE_BIT);
}

#define EVENTS_READY_BIT (0)

uint8_t SPI_transfer(uint8_t data) {
    spi[0]->TXD = data;

    while (!spi[0]->EVENTS_READY) {
        ;
    }

    SET_BIT_LO(spi[0]->EVENTS_READY, EVENTS_READY_BIT);
    return spi[0]->RXD;
}

static void setSpeed(SPI_Speed speed) {
    if ( speed == K125 ) {
        spi[0]->FREQUENCY = 0x02000000;
    } else if ( speed == K250) {
        spi[0]->FREQUENCY = 0x04000000;
    } else if ( speed == K500) {
        spi[0]->FREQUENCY = 0x08000000;
    } else if ( speed == M1) {
        spi[0]->FREQUENCY = 0x10000000;
    } else if ( speed == M2) {
        spi[0]->FREQUENCY = 0x20000000;
    } else if ( speed == M4) {
        spi[0]->FREQUENCY = 0x40000000;
    } else if ( speed == M8) {
        spi[0]->FREQUENCY = 0x80000000;
    } else {
        setSpeed(M4); // should not get here
    }
}

#define CPHA (1)
#define CPOL (2)

static void setMode(SPI_Mode mode) {
    if ( mode == SPI_MODE0 ) {
        SET_BIT_LO(spi[0]->CONFIG, CPHA);
        SET_BIT_LO(spi[0]->CONFIG, CPOL);
    } else if ( mode == SPI_MODE1 ) {
        SET_BIT_HI(spi[0]->CONFIG, CPHA);
        SET_BIT_LO(spi[0]->CONFIG, CPOL);
    } else if ( mode == SPI_MODE2 ) {
        SET_BIT_LO(spi[0]->CONFIG, CPHA);
        SET_BIT_HI(spi[0]->CONFIG, CPOL);
    } else if ( mode == SPI_MODE3 ) {
        SET_BIT_HI(spi[0]->CONFIG, CPHA);
        SET_BIT_HI(spi[0]->CONFIG, CPOL);
    } else {
        setMode(SPI_MODE0); // should not get here
    }
}

#define ORDER (0)

static void setBitOrder(SPI_BitOrder bitOrder) {
    if ( bitOrder == MSB_FIRST ) {
        SET_BIT_LO(spi[0]->CONFIG, ORDER);
    } else if ( bitOrder == LSB_FIRST ) {
        SET_BIT_HI(spi[0]->CONFIG, ORDER);
    } else {
        setBitOrder(MSB_FIRST);    // sould not get here
    }
}

#define PORT_BIT (5)
#define ENABLE_BIT (31)

static void setSckPinPort(nRF_PinPort sckPinPort) {
    spi[0]->PSEL_SCK = sckPinPort.pin;
    if ( sckPinPort.port == PORT_0 ) {
        SET_BIT_LO(spi[0]->PSEL_SCK, PORT_BIT);
    } else {
        SET_BIT_HI(spi[0]->PSEL_SCK, PORT_BIT);
    }
    SET_BIT_HI(spi[0]->PSEL_SCK, ENABLE_BIT);
}

static void setMosiPinPort(nRF_PinPort sckMosiPort) {
    spi[0]->PSEL_MOSI = mosiPinPort.pin;
    if ( mosiPinPort.port == PORT_0 ) {
        SET_BIT_LO(spi[0]->PSEL_MOSI, PORT_BIT);
    } else {
        SET_BIT_HI(spi[0]->PSEL_MOSI, PORT_BIT);
    }
    SET_BIT_HI(spi[0]->PSEL_MOSI, ENABLE_BIT);
}

static void setMisoPinPort(nRF_PinPort misoPinPort) {
    spi[0]->PSEL_MISO = misoPinPort.pin;
    if ( misoPinPort.port == PORT_0 ) {
        SET_BIT_LO(spi[0]->PSEL_MISO, PORT_BIT);
    } else {
        SET_BIT_HI(spi[0]->PSEL_MISO, PORT_BIT);
    }
    SET_BIT_HI(spi[0]->PSEL_MISO, ENABLE_BIT);
}

void SPI_configure(SPI_Config *config) {
    setSpeed(config->speed);
    setMode(config->mode);
    setBitOrder(config->bitOrder);
    setSckPinPort(config->sckPin);
    setMosiPinPort(config->mosiPin);
    setMisoPinPort(config->misoPin);
}
