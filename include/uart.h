#ifndef UART_H
#define UART_H

#include <stdbool.h>
#include <gpio.h>

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

void UART_startRx(void);
void UART_stopRx(void);
void UART_startTx(void);
void UART_stopTx(void);
void UART_suspend(void);

bool UART_isEventCts(void);
bool UART_isEventNcts(void);
bool UART_isEventRxRdy(void);
bool UART_isEventTxRdy(void);
bool UART_isEventError(void);
bool UART_isEventRxTo(void);

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
void UART_enableHardwareFlowCtrl();
void UART_disableHardwareFlowCtrl();
void UART_includeParityBit(void);
void UART_excludeParityBit(void);

#endif  // UART_H
