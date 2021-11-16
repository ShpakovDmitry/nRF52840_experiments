/*
 *   file: uart.h
 * author: ShpakovDmitry
 *   date: 2021-11-16
 */

#ifndef UART_H
#define UART_H

#include <stdbool.h>
#include <stddef.h>
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UART_RX_BUFF_SIZE   1024
#define UART_TX_BUFF_SIZE   1024

typedef enum {
    UART_SHORT_CTS_STARTRX,
    UART_SHORT_NCTS_STOPRX
} UART_Shortcuts;

typedef enum {
    UART_INT_CTS,
    UART_INT_NCTS,
    UART_INT_RXDRDY,
    UART_INT_TXDRDY,
    UART_INT_ERROR,
    UART_INT_RXTO
} UART_Interrupts;

typedef enum {
    UART_ERROR_OVERRUN,
    UART_ERROR_PARITY,
    UART_ERROR_FRAMING,
    UART_ERROR_BREAK
} UART_ErrorSources;

typedef enum {
    UART_PIN_RTS,
    UART_PIN_TXD,
    UART_PIN_CTS,
    UART_PIN_RXD
} UART_Pin;

typedef enum {
    UART_BAUD_1200,
    UART_BAUD_2400,
    UART_BAUD_4800,
    UART_BAUD_9600,
    UART_BAUD_14400,
    UART_BAUD_19200,
    UART_BAUD_28800,
    UART_BAUD_31250,
    UART_BAUD_38400,
    UART_BAUD_56000,
    UART_BAUD_57600,
    UART_BAUD_76800,
    UART_BAUD_115200,
    UART_BAUD_230400,
    UART_BAUD_250000,
    UART_BAUD_460800,
    UART_BAUD_921600,
    UART_BAUD_1M
} UART_BaudRates;

typedef enum {
    UART_ONE_STOP_BIT,
    UART_TWO_STOP_BITS
} UART_StopBits;

typedef enum {
    UART_EVENT_CTS,
    UART_EVENT_NCTS,
    UART_EVENT_RXDRDY,
    UART_EVENT_TXDRDY,
    UART_EVENT_ERROR,
    UART_EVENT_RXTO
} UART_Events;

typedef enum {
    UART_TASK_STARTRX,
    UART_TASK_STOPRX,
    UART_TASK_STARTTX,
    UART_TASK_STOPTX,
    UART_TASK_SUSPEND
} UART_Tasks;

void UART_startTask(UART_Tasks task);
bool UART_isEvent(UART_Events event);
void UART_clearEvent(UART_Events event);

void UART_enableShort(UART_Shortcuts shortcut);
void UART_disableShort(UART_Shortcuts shortcut);

void UART_enableInterrupt(UART_Interrupts interrupt);
void UART_disableInterrupt(UART_Interrupts interrupt);

bool UART_isErrorSource(UART_ErrorSources errorSource);

void UART_enable(void);
void UART_disable(void);

void UART_connectPin(UART_Pin uartPin, GPIO_Port gpioPort, GPIO_Pin gpioPin);
void UART_disconnectPin(UART_Pin uartPin, GPIO_Port gpioPort, GPIO_Pin gpioPin);
void UART_readRxd(uint8_t* data);
void UART_writeTxd(uint8_t data);
void UART_setBaudrate(UART_BaudRates baudRate);
void UART_enableHardwareFlowCtrl(void);
void UART_disableHardwareFlowCtrl(void);
void UART_includeParityBit(void);
void UART_excludeParityBit(void);
void UART_setStopBits(UART_StopBits stopBits);

size_t UART_sendData(uint8_t* data, size_t size);
bool UART_sendByte(uint8_t data);
size_t UART_sendString(char* str);

size_t UART_getData(uint8_t* data, size_t size);

void UART_initBuffers(void);

#ifdef __cplusplus
}
#endif

#endif  // UART_H
