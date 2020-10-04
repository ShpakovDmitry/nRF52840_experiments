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
bool UART_readRxd(uint8_t* data);
void UART_writeTxd(uint8_t data);
bool UART_setBaudrate(uint32_t baudRate);
void UART_setHardwareFlowCtrl();

#endif  // UART_H
