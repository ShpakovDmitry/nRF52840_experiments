/*
 *   file: spi.h
 * author: ShpakovDmitry
 *   date: 2022-06-27
 */

#ifndef SPI_H
#define SPI_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus


typedef enum {
    SPI_MODE0,  // CPOL == 0 CPHA == 0
    SPI_MODE1,  // CPOL == 0 CPHA == 1
    SPI_MODE2,  // CPOL == 1 CPHA == 0
    SPI_MODE3   // CPOL == 1 CPHA == 1
} SPI_Mode;

typedef enum {
    K125,       // 125 kbps data rate
    K250,       // 250 kbps data rate
    K500,       // 500 kbps data rate
    M1,         // 1 Mbps data rate
    M2,         // 2 Mbps data rate
    M4,         // 4 Mbps data rate
    M8          // 8 Mbps data rate
} SPI_Speed;

typedef enum {
    MSB_FIRST,  // Most significant bit shifted out first
    LSB_FIRST   // Least significant bit shifted out first
} SPI_BitOrder;

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
    nRF_Port port;
    nRF_Pin pin;
} nRF_PinPort;

typedef struct {
    SPI_Speed speed;
    SPI_Mode mode;
    SPI_BitOrder bitOrder;
    nRF_PinPort sckPin
    nRF_PinPort mosiPin;
    nRF_PinPort misoPin;
} SPI_Config;

void SPI_configure(SPI_Config *config);
void SPI_enable();
void SPI_disable();
uint8_t SPI_transfer(uint8_t data);


#ifdef __cplusplus
}
#endif//__cplusplus

#endif//SPI_H
