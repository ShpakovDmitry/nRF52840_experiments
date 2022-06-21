/*
 *   file: spim0.h
 * author: ShpakovDmitry
 *   date: 2022-06-21
 */

#ifndef SPIM0_H
#define SPIM0_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

typedef enum {
    K125,       // 125 kbps data rate
    K250,       // 250 kbps data rate
    K500,       // 500 kbps data rate
    M1,         // 1 Mbps data rate
    M2,         // 2 Mbps data rate
    M4,         // 4 Mbps data rate
    M8,         // 8 Mbps data rate
    M16,        // 16 Mbps data rate
    M32         // 32 Mbps data rate
} SPIM0_Speed;

typedef enum {
    SPI_MODE0,  // CPOL == 0 CPHA == 0
    SPI_MODE1,  // CPOL == 0 CPHA == 1
    SPI_MODE2,  // CPOL == 1 CPHA == 0
    SPI_MODE3   // CPOL == 1 CPHA == 1
} SPIM0_Mode;

typedef enum {
    MSB_FIRST,  // Most significant bit shifted out first
    LSB_FIRST   // Least significant bit shifted out first
} SPIM0_BitOrder;

typedef enum {
    PORT_0 = 0,
    PORT_1
} nRF_Port;

typedef enum {
    PIN_0 = 0,  PIN_1,  PIN_2,  PIN_3,  PIN_4,  PIN_5,  PIN_6,  PIN_7,
    PIN_8,  PIN_9,  PIN_10, PIN_11, PIN_12, PIN_13, PIN_14, PIN_15,
    PIN_16, PIN_17, PIN_18, PIN_19, PIN_20, PIN_21, PIN_22, PIN_23,
    PIN_24, PIN_25, PIN_26, PIN_27, PIN_28, PIN_29, PIN_30, PIN_31
} nRF_Pin;


typedef struct {
    SPIM0_Speed speed;
    SPIM0_Mode mode;
    SPIM0_BitOrder bitOrder;
    nRF_Port sckPort;
    nRF_Pin  sckPin;
    nRF_Port misoPort;
    nRF_Pin  misoPin;
    nRF_Port mosiPort;
    nRF_Pin  mosiPin;
    nRF_Port csnPort;
    nRF_Pin  csnPin;
} SPIM0_Config;

void SPIM0_configure(SPIM0_Config *config);
void SPIM0_setReceiveBuffer(uint8_t *buf, size_t size);
void SPIM0_setTransmitBuffer(uint8_t *buf, size_t size);
void SPIM0_enable();
void SPIM0_disable();
void SPIM0_transfer();



#ifdef __cplusplus
}
#endif//__cplusplus

#endif//SPIM0_H
