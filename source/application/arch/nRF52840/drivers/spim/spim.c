/*
 *   file: spim.c
 * author: ShpakovDmitry
 *   date: 2022-06-21
 */

#include <stdint.h>

#include "spim.h"

#define SPIM0_BASE_ADDRESS (0x40003000u)
#define SPIM1_BASE_ADDRESS (0x40004000u)
#define SPIM2_BASE_ADDRESS (0x40023000u)
#define SPIM3_BASE_ADDRESS (0x4002F000u)

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

SpimRegisters *spim[4] = {
    (SpimRegisters *) SPIM0_BASE_ADDRESS,
    (SpimRegisters *) SPIM1_BASE_ADDRESS,
    (SpimRegisters *) SPIM2_BASE_ADDRESS,
    (SpimRegisters *) SPIM3_BASE_ADDRESS
};
