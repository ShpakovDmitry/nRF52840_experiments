/*
 *   file: spim0.c
 * author: ShpakovDmitry
 *   date: 2022-06-21
 */

#include <stdint.h>
#include <stddef.h>

#include "spim0.h"

#define SPIM0_BASE_ADDRESS 0x40003000u
#define SPIM1_BASE_ADDRESS 0x40004000u
#define SPIM2_BASE_ADDRESS 0x40023000u
#define SPIM3_BASE_ADDRESS 0x4002F000u

typedef volatile struct __attribute__((packed)) {
    uint32_t reserved[4];           /**/
    uint32_t TASKS_START;           /**/
    uint32_t TASKS_STOP;            /**/
    uint32_t reserved1[1];          /**/
    uint32_t TASKS_SUSPEND;         /**/
    uint32_t TASKS_RESUME;          /**/
    uint32_t reserved2[56];         /**/
    uint32_t EVENTS_STOPPED;        /**/
    uint32_t reserved3[2];          /**/
    uint32_t EVENTS_ENDRX;          /**/
    uint32_t reserved4[1];          /**/
    uint32_t EVENTS_END;            /**/
    uint32_t reserved5[1];          /**/
    uint32_t EVENTS_ENDTX;          /**/
    uint32_t reserved6[10];         /**/
    uint32_t EVENTS_STARTED;        /**/
    uint32_t reserved7[44];         /**/
    uint32_t SHORTS;                /**/
    uint32_t reserved8[64];         /**/
    uint32_t INTENSET;              /**/
    uint32_t INTENCLR;              /**/
    uint32_t reserved9[61];         /**/
    uint32_t STALLSTAT;             /**/
    uint32_t reserved10[63];        /**/
    uint32_t ENABLE;                /**/
    uint32_t reserved11[1];         /**/
    uint32_t PSEL_SCK;              /**/
    uint32_t PSEL_MOSI;             /**/
    uint32_t PSEL_MISO;             /**/
    uint32_t PSEL_CSN;              /**/
    uint32_t reserved12[3];         /**/
    uint32_t FREQUENCY;             /**/
    uint32_t reserved13[3];         /**/
    uint32_t RXD_PTR;               /**/
    uint32_t RXD_MAXCNT;            /**/
    uint32_t RXD_AMOUNT;            /**/
    uint32_t RXD_LIST;              /**/
    uint32_t TXD_PTR;               /**/
    uint32_t TXD_MAXCNT;            /**/
    uint32_t TXD_AMOUNT;            /**/
    uint32_t TXD_LIST;              /**/
    uint32_t CONFIG;                /**/
    uint32_t reserved14[2];         /**/
    uint32_t IFTIMING_RXDELAY;      /**/
    uint32_t IFTIMING_CSNDUR;       /**/
    uint32_t CSNPOL;                /**/
    uint32_t PSELDCX;               /**/
    uint32_t DCXCNT;                /**/
    uint32_t reserved15[19];        /**/
    uint32_t ORC;                   /**/
} SpimRegisters;

static SpimRegisters *spim0 = (SpimRegisters *) SPIM0_BASE_ADDRESS;

#define SET_BIT_HI(reg, bit) ( (reg) |=  (1 << (bit)) )
#define SET_BIT_LO(reg, bit) ( (reg) &= ~(1 << (bit)) )

void SPIM0_enable() {
    spim0->ENABLE = 0x00000007u;
}

void SPIM0_disable() {
    spim0->ENABLE = 0x00000000u;
}

void SPIM0_setReceiveBuffer(uint8_t *buf, size_t size) {
    spim0->RXD_PTR = (uint32_t)((uint32_t *)buf);
    spim0->RXD_MAXCNT = size;
}

void SPIM0_setTransmitBuffer(uint8_t *buf, size_t size) {
    spim0->TXD_PTR = (uint32_t)((uint32_t *)buf);
    spim0->TXD_MAXCNT = size;
}

void SPIM0_transfer() {
    spim0->TASKS_START = 0x00000001u;

    while (!spim0->EVENTS_END) {
        ;
    }

    spim0->EVENTS_END = 0x00000000u;
}

static void setSpeed(SPIM0_Speed speed) {
    if ( speed == K125 ) {
        spim0->FREQUENCY = 0x02000000;
    } else if ( speed == K250) {
        spim0->FREQUENCY = 0x04000000;
    } else if ( speed == K500) {
        spim0->FREQUENCY = 0x08000000;
    } else if ( speed == M1) {
        spim0->FREQUENCY = 0x10000000;
    } else if ( speed == M2) {
        spim0->FREQUENCY = 0x20000000;
    } else if ( speed == M4) {
        spim0->FREQUENCY = 0x40000000;
    } else if ( speed == M8) {
        spim0->FREQUENCY = 0x80000000;
    } else if ( speed == M16) {
        spim0->FREQUENCY = 0x0A000000;
    } else if ( speed == M32) {
        spim0->FREQUENCY = 0x14000000;
    } else {
        setSpeed(M4); // should not get here
    }
}

#define CPHA (1)
#define CPOL (2)

static void setMode(SPIM0_Mode mode) {
    if ( mode == SPI_MODE0 ) {
        SET_BIT_LO(spim0->CONFIG, CPHA);
        SET_BIT_LO(spim0->CONFIG, CPOL);
    } else if ( mode == SPI_MODE1 ) {
        SET_BIT_HI(spim0->CONFIG, CPHA);
        SET_BIT_LO(spim0->CONFIG, CPOL);
    } else if ( mode == SPI_MODE2 ) {
        SET_BIT_LO(spim0->CONFIG, CPHA);
        SET_BIT_HI(spim0->CONFIG, CPOL);
    } else if ( mode == SPI_MODE3 ) {
        SET_BIT_HI(spim0->CONFIG, CPHA);
        SET_BIT_HI(spim0->CONFIG, CPOL);
    } else {
        setMode(SPI_MODE0); // should not get here
    }
}

#define ORDER 0

static void setBitOrder(SPIM0_BitOrder bitOrder) {
    if ( bitOrder == MSB_FIRST ) {
        SET_BIT_LO(spim0->CONFIG, ORDER);
    } else if ( bitOrder == LSB_FIRST ) {
        SET_BIT_HI(spim0->CONFIG, ORDER);
    } else {
        setBitOrder(MSB_FIRST);    // sould not get here
    }
}

#define PORT_BIT 5
#define ENABLE_BIT 31

static void setSckPort(nRF_Port port, nRF_Pin pin) {
    spim0->PSEL_SCK = pin;
    if ( port == PORT_0 ) {
        SET_BIT_LO(spim0->PSEL_SCK, PORT_BIT);
    } else {
        SET_BIT_HI(spim0->PSEL_SCK, PORT_BIT);
    }
    SET_BIT_HI(spim0->PSEL_SCK, ENABLE_BIT);
}

static void setMisoPort(nRF_Port port, nRF_Pin pin) {
    spim0->PSEL_MISO = pin;
    if ( port == PORT_0 ) {
        SET_BIT_LO(spim0->PSEL_MISO, PORT_BIT);
    } else {
        SET_BIT_HI(spim0->PSEL_MISO, PORT_BIT);
    }
    SET_BIT_HI(spim0->PSEL_MISO, ENABLE_BIT);
}

static void setMosiPort(nRF_Port port, nRF_Pin pin) {
    spim0->PSEL_MOSI = pin;
    if ( port == PORT_0 ) {
        SET_BIT_LO(spim0->PSEL_MOSI, PORT_BIT);
    } else {
        SET_BIT_HI(spim0->PSEL_MOSI, PORT_BIT);
    }
    SET_BIT_HI(spim0->PSEL_MOSI, ENABLE_BIT);
}

static void setCsnPort(nRF_Port port, nRF_Pin pin) {
    spim0->PSEL_CSN= pin;
    if ( port == PORT_0 ) {
        SET_BIT_LO(spim0->PSEL_CSN, PORT_BIT);
    } else {
        SET_BIT_HI(spim0->PSEL_CSN, PORT_BIT);
    }
    SET_BIT_HI(spim0->PSEL_CSN, ENABLE_BIT);
}

void SPIM0_configure(SPIM0_Config *config) {
    setSpeed(config->speed);
    setMode(config->mode);
    setBitOrder(config->bitOrder);
    setSckPort(config->sckPort, config->sckPin);
    setMisoPort(config->misoPort, config->misoPin);
    setMosiPort(config->mosiPort, config->mosiPin);
    setCsnPort(config->csnPort, config->csnPin);
}
