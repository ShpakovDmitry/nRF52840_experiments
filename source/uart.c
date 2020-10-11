#include <uart.h>
#include <stdint.h>
#include <ringbuffer.h>
#include <string.h>
#include <stddef.h>

static uint8_t g_receiveBuffer[UART_RX_BUFF_SIZE];
static uint8_t g_transmittBuffer[UART_TX_BUFF_SIZE];
static RingBuffer g_rxBuff;
static RingBuffer g_txBuff;
static RingBufferHandle rxBuffHandle;
static RingBufferHandle txBuffHandle;

#define UART_BASE_ADDRESS 0x40002000u

typedef volatile struct __attribute__((packed)) {
    uint32_t TASKS_STARTRX;     // 0x000 Start UART receiver
    uint32_t TASKS_STOPRX;      // 0x004 Stop UART receiver
    uint32_t TASKS_STARTTX;     // 0x008 Start UART transmitter
    uint32_t TASKS_STOPTX;      // 0x00C Stop UART transmitter
    uint32_t reserved0[3];      // 0x010 - 0x018 reserved
    uint32_t TASKS_SUSPEND;     // 0x01C Suspend UART
    uint32_t reserved1[56];     // 0x020 - 0x0FC reserved
    uint32_t EVENTS_CTS;        // 0x100 CTS is activated
    uint32_t EVENTS_NCTS;       // 0x104 CTS is deactivated
    uint32_t EVENTS_RXDRDY;     // 0x108 Data received in RXD
    uint32_t reserved2[4];      // 0x10C - 0x118 reserved
    uint32_t EVENTS_TXDRDY;     // 0x11C Data sent from TXD
    uint32_t reserved3[1];      // 0x120 reserved
    uint32_t EVENTS_ERROR;      // 0x124 Error detected
    uint32_t reserved4[7];      // 0x128 - 0x140 reserved
    uint32_t EVENTS_RXTO;       // 0x144 Receiver timeout
    uint32_t reserved5[46];     // 0x148 - 0x1FC reserved
    uint32_t SHORTS;            // 0x200 Shortcuts between local events/tasks
    uint32_t reserved6[64];     // 0x204 - 0x300 reserved
    uint32_t INTENSET;          // 0x304 Enable interrupt
    uint32_t INTENCLR;          // 0x308 Disable interrupt
    uint32_t reserved7[93];     // 0x30C - 0x47C reserved
    uint32_t ERRORSRC;          // 0x480 Error source
    uint32_t reserved8[31];     // 0x484 - 0x4FC reserved
    uint32_t ENABLE;            // 0x500 Enable UART
    uint32_t reserved9[1];      // 0x504 reserved
    uint32_t PSEL_RTS;          // 0x508 Pin select for RTS
    uint32_t PSEL_TXD;          // 0x50C Pin select for TXD
    uint32_t PSEL_CTS;          // 0x510 Pin select for CTS
    uint32_t PSEL_RXD;          // 0x514 Pin select for RXD
    uint32_t RXD;               // 0x518 RXD register
    uint32_t TXD;               // 0x51C TXD register
    uint32_t reserved10[1];     // 0x520 reserved
    uint32_t BAUDRATE;          // 0x524 Baud rate
    uint32_t reserved11[17];    // 0x528 - 0x568 reserved
    uint32_t CONFIG;            // 0x56C Config. of parity and HW flow ctrl.
}UART_Registers;

static UART_Registers* uart = (UART_Registers *) UART_BASE_ADDRESS;

#define TASKS_STARTRX_BIT   0
#define TASKS_STOPRX_BIT    0
#define TASKS_STARTTX_BIT   0
#define TASKS_STOPTX_BIT    0
#define TASKS_SUSPEND_BIT   0

#define EVENTS_CTS_BIT      0
#define EVENTS_NCTS_BIT     0
#define EVENTS_RXDRDY_BIT   0
#define EVENTS_TXDRDY_BIT   0
#define EVENTS_ERROR_BIT    0
#define EVENTS_RXTO_BIT     0

#define SHORTS_CTS_STARTRX_BIT  3
#define SHORTS_NCTS_STOPTRX_BIT 4

#define INT_CTS_BIT     0
#define INT_NCTS_BIT    1
#define INT_RXDRDY_BIT  2
#define INT_TXDRDY_BIT  7
#define INT_ERROR_BIT   9
#define INT_RXTO_BIT    17

#define ERROR_OVERRUN_BIT   0
#define ERROR_PARITY_BIT    1
#define ERROR_FRAMING_BIT   2
#define ERROR_BREAK_BIT     3

#define ENABLE_BIT  2

#define PIN_BIT     0
#define PORT_BIT    5
#define CONNECT_BIT 31
#define CONNECT     0
#define DISCONNECT  1

#define HWFC_BIT    0

#define PARITY_INCLUDE_REG_VAL 7
#define PARITY_INCLUDE_BIT     1

#define STOP_BITS_BIT   4

#define SET_BIT_HI(reg, bit) ( (reg) |=  (1 << (bit)) )
#define SET_BIT_LO(reg, bit) ( (reg) &= ~(1 << (bit)) )
#define GET_BIT(reg, bit)    ( (reg)  &  (1 << (bit)) )
#define SET_REG_VAL(reg, val) ( (reg) = (val) )

void UART_startTask(UART_Tasks task) {
    switch (task) {
        case UART_TASK_STARTRX:
            SET_BIT_HI(uart->TASKS_STARTRX, TASKS_STARTRX_BIT);
            break;
        case UART_TASK_STOPRX:
            SET_BIT_HI(uart->TASKS_STOPRX, TASKS_STOPRX_BIT);
            break;
        case UART_TASK_STARTTX:
            SET_BIT_HI(uart->TASKS_STARTTX, TASKS_STARTTX_BIT);
            break;
        case UART_TASK_STOPTX:
            SET_BIT_HI(uart->TASKS_STOPTX, TASKS_STOPTX_BIT);
            break;
        case UART_TASK_SUSPEND:
            SET_BIT_HI(uart->TASKS_SUSPEND, TASKS_SUSPEND_BIT);
            break;
        default:    // nothing to do here
            break;
    }
}

bool UART_isEvent(UART_Events event) {
    bool res = false;
    switch (event) {
        case UART_EVENT_CTS:
            res = GET_BIT(uart->EVENTS_CTS, EVENTS_CTS_BIT) ? true : false;
            break;
        case UART_EVENT_NCTS:
            res = GET_BIT(uart->EVENTS_NCTS, EVENTS_NCTS_BIT) ? true : false;
            break;
        case UART_EVENT_RXDRDY:
            res = GET_BIT(uart->EVENTS_RXDRDY, EVENTS_RXDRDY_BIT) ? true : false;
            break;
        case UART_EVENT_TXDRDY:
            res = GET_BIT(uart->EVENTS_TXDRDY, EVENTS_TXDRDY_BIT) ? true : false;
            break;
        case UART_EVENT_ERROR:
            res = GET_BIT(uart->EVENTS_ERROR, EVENTS_ERROR_BIT) ? true : false;
            break;
        case UART_EVENT_RXTO:
            res = GET_BIT(uart->EVENTS_RXTO, EVENTS_RXTO_BIT) ? true : false;
            break;
        default:    // nothing to do here
            break;
    }
    return res;
}

void UART_clearEvent(UART_Events event) {
     switch (event) {
        case UART_EVENT_CTS:
            SET_BIT_LO(uart->EVENTS_CTS, EVENTS_CTS_BIT);
            break;
        case UART_EVENT_NCTS:
            SET_BIT_LO(uart->EVENTS_NCTS, EVENTS_NCTS_BIT);
            break;
        case UART_EVENT_RXDRDY:
            SET_BIT_LO(uart->EVENTS_RXDRDY, EVENTS_RXDRDY_BIT);
            break;
        case UART_EVENT_TXDRDY:
            SET_BIT_LO(uart->EVENTS_TXDRDY, EVENTS_TXDRDY_BIT);
            break;
        case UART_EVENT_ERROR:
            SET_BIT_LO(uart->EVENTS_ERROR, EVENTS_ERROR_BIT);
            break;
        case UART_EVENT_RXTO:
            SET_BIT_LO(uart->EVENTS_RXTO, EVENTS_RXTO_BIT);
            break;
        default:    // nothing to do here
            break;
    }
}

void UART_enableShort(UART_Shortcuts shortcut) {
    switch (shortcut) {
        case UART_SHORT_CTS_STARTRX:
            SET_BIT_HI(uart->SHORTS, SHORTS_CTS_STARTRX_BIT);
            break;
        case UART_SHORT_NCTS_STOPRX:
            SET_BIT_HI(uart->SHORTS, SHORTS_NCTS_STOPTRX_BIT);
            break;
        default:    // nothing to do here
            break;
    }
}

void UART_disableShort(UART_Shortcuts shortcut) {
    switch (shortcut) {
        case UART_SHORT_CTS_STARTRX:
            SET_BIT_LO(uart->SHORTS, SHORTS_CTS_STARTRX_BIT);
            break;
        case UART_SHORT_NCTS_STOPRX:
            SET_BIT_LO(uart->SHORTS, SHORTS_NCTS_STOPTRX_BIT);
            break;
        default:    // nothing to do here
            break;
    }
}

void UART_enableInterrupt(UART_Interrupts interrupt) {
    switch (interrupt) {
        case UART_INT_CTS:
            SET_BIT_HI(uart->INTENSET, INT_CTS_BIT);
            break;
        case UART_INT_NCTS:
            SET_BIT_HI(uart->INTENSET, INT_NCTS_BIT);
            break;
        case UART_INT_RXDRDY:
            SET_BIT_HI(uart->INTENSET, INT_RXDRDY_BIT);
            break;
        case UART_INT_TXDRDY:
            SET_BIT_HI(uart->INTENSET, INT_TXDRDY_BIT);
            break;
        case UART_INT_ERROR:
            SET_BIT_HI(uart->INTENSET, INT_ERROR_BIT);
            break;
        case UART_INT_RXTO:
            SET_BIT_HI(uart->INTENSET, INT_RXTO_BIT);
            break;
        default:    // nothing to do here
            break;
    }
}

void UART_disableInterrupt(UART_Interrupts interrupt) {
    switch (interrupt) {
        case UART_INT_CTS:
            SET_BIT_HI(uart->INTENCLR, INT_CTS_BIT);
            break;
        case UART_INT_NCTS:
            SET_BIT_HI(uart->INTENCLR, INT_NCTS_BIT);
            break;
        case UART_INT_RXDRDY:
            SET_BIT_HI(uart->INTENCLR, INT_RXDRDY_BIT);
            break;
        case UART_INT_TXDRDY:
            SET_BIT_HI(uart->INTENCLR, INT_TXDRDY_BIT);
            break;
        case UART_INT_ERROR:
            SET_BIT_HI(uart->INTENCLR, INT_ERROR_BIT);
            break;
        case UART_INT_RXTO:
            SET_BIT_HI(uart->INTENCLR, INT_RXTO_BIT);
            break;
        default:    // nothing to do here
            break;
    }
}

bool UART_isErrorSource(UART_ErrorSources errorSource) {
    bool res = false;
    switch (errorSource) {
        case UART_ERROR_OVERRUN:
            if ( GET_BIT(uart->ERRORSRC, ERROR_OVERRUN_BIT) ){
                res = true;
            }
            break;
        case UART_ERROR_PARITY:
            if ( GET_BIT(uart->ERRORSRC, ERROR_PARITY_BIT) ){
                res = true;
            }
            break;
        case UART_ERROR_FRAMING:
            if ( GET_BIT(uart->ERRORSRC, ERROR_FRAMING_BIT) ){
                res = true;
            }
            break;
        case UART_ERROR_BREAK:
            if ( GET_BIT(uart->ERRORSRC, ERROR_BREAK_BIT) ){
                res = true;
            }
            break;
        default:    // nothing to do here
            break;
    }
    return res;
}

void UART_enable(void) {
    SET_BIT_HI(uart->ENABLE, ENABLE_BIT);
}

void UART_disable(void) {
    SET_BIT_LO(uart->ENABLE, ENABLE_BIT);
}

void UART_connectPin(UART_Pin uartPin, GPIO_Port gpioPort, GPIO_Pin gpioPin) {
    switch (uartPin) {
        case UART_PIN_RTS:
            uart->PSEL_RTS = (CONNECT << CONNECT_BIT) | (gpioPort << PORT_BIT) |
                             (gpioPin << PIN_BIT);
            break;
        case UART_PIN_TXD:
            uart->PSEL_TXD = (CONNECT << CONNECT_BIT) | (gpioPort << PORT_BIT) |
                             (gpioPin << PIN_BIT);
            break;
        case UART_PIN_CTS:
            uart->PSEL_CTS = (CONNECT << CONNECT_BIT) | (gpioPort << PORT_BIT) |
                             (gpioPin << PIN_BIT);
            break;
        case UART_PIN_RXD:
            uart->PSEL_RXD = (CONNECT << CONNECT_BIT) | (gpioPort << PORT_BIT) |
                             (gpioPin << PIN_BIT);
            break;
        default:    // nothing to do here
            break;

    }
}

void UART_disconnectPin(UART_Pin uartPin, GPIO_Port gpioPort, GPIO_Pin gpioPin) {
    switch (uartPin) {
        case UART_PIN_RTS:
            uart->PSEL_RTS = (DISCONNECT << CONNECT_BIT) | (gpioPort << PORT_BIT) |
                             (gpioPin << PIN_BIT);
            break;
        case UART_PIN_TXD:
            uart->PSEL_TXD = (DISCONNECT << CONNECT_BIT) | (gpioPort << PORT_BIT) |
                             (gpioPin << PIN_BIT);
            break;
        case UART_PIN_CTS:
            uart->PSEL_CTS = (DISCONNECT << CONNECT_BIT) | (gpioPort << PORT_BIT) |
                             (gpioPin << PIN_BIT);
            break;
        case UART_PIN_RXD:
            uart->PSEL_RXD = (DISCONNECT << CONNECT_BIT) | (gpioPort << PORT_BIT) |
                             (gpioPin << PIN_BIT);
            break;
        default:    // nothing to do here
            break;

    }

}

void UART_readRxd(uint8_t* data) {
    *data = uart->RXD;
}

void UART_writeTxd(uint8_t data) {
    uart->TXD = data;
}

void UART_setBaudrate(UART_BaudRates baudRate) {
    uint32_t baudRegVal;
    switch (baudRate) {
        case UART_BAUD_1200:   {baudRegVal = 0x0004f000; break; }
        case UART_BAUD_2400:   {baudRegVal = 0x0009d000; break; }
        case UART_BAUD_4800:   {baudRegVal = 0x0013b000; break; }
        case UART_BAUD_9600:   {baudRegVal = 0x00275000; break; }
        case UART_BAUD_14400:  {baudRegVal = 0x003b0000; break; }
        case UART_BAUD_19200:  {baudRegVal = 0x004ea000; break; }
        case UART_BAUD_28800:  {baudRegVal = 0x0075f000; break; }
        case UART_BAUD_31250:  {baudRegVal = 0x00800000; break; }
        case UART_BAUD_38400:  {baudRegVal = 0x009d5000; break; }
        case UART_BAUD_56000:  {baudRegVal = 0x00e50000; break; }
        case UART_BAUD_57600:  {baudRegVal = 0x00ebf000; break; }
        case UART_BAUD_76800:  {baudRegVal = 0x013a9000; break; }
        case UART_BAUD_115200: {baudRegVal = 0x01d7e000; break; }
        case UART_BAUD_230400: {baudRegVal = 0x03afb000; break; }
        case UART_BAUD_250000: {baudRegVal = 0x04000000; break; }
        case UART_BAUD_460800: {baudRegVal = 0x075f7000; break; }
        case UART_BAUD_921600: {baudRegVal = 0x0ebed000; break; }
        case UART_BAUD_1M:     {baudRegVal = 0x10000000; break; }
        default:               {baudRegVal = 0x00000000; break; }
    }
    
    SET_REG_VAL(uart->BAUDRATE, baudRegVal);
}

void UART_enableHardwareFlowCtrl(void) {
    SET_BIT_HI(uart->CONFIG, HWFC_BIT);
}

void UART_disableHardwareFlowCtrl(void) {
    SET_BIT_LO(uart->CONFIG, HWFC_BIT);
}

void UART_includeParityBit(void) {
    uart->CONFIG |= (PARITY_INCLUDE_REG_VAL << PARITY_INCLUDE_BIT);
}

void UART_excludeParityBit(void) {
    uart->CONFIG &= ~(PARITY_INCLUDE_REG_VAL << PARITY_INCLUDE_BIT);
}

void UART_setStopBits(UART_StopBits stopBits) {
    switch (stopBits) {
        case UART_ONE_STOP_BIT:
            SET_BIT_LO(uart->CONFIG, STOP_BITS_BIT);
            break;
        case UART_TWO_STOP_BITS:
            SET_BIT_HI(uart->CONFIG, STOP_BITS_BIT);
            break;
        default:    // nothing to do here
            break;
    }
}

size_t UART_sendData(uint8_t* data, size_t size) {
    if (data == NULL || size == 0) {
        return 0;
    }

    size_t bytesSent = 0;
    UART_disableInterrupt(UART_INT_TXDRDY);
    for(size_t i = 0; i < size; i++) {
        if ( RingBuffer_put2(txBuffHandle, data[i]) == false ) {
            break;
        }
        bytesSent++;
    }
    if (UART_isEvent(UART_EVENT_TXDRDY) == false ) {
        uint8_t tmp;
        if ( RingBuffer_get(txBuffHandle, &tmp) == true ) {
            UART_startTask(UART_TASK_STARTTX);
            UART_writeTxd(tmp);
        }
    }
    UART_enableInterrupt(UART_INT_TXDRDY);

    return bytesSent;
}

bool UART_sendByte(uint8_t data) {
    bool res = false;
    if ( UART_sendData(&data, 1) == 1 ) {
        res = true;
    }
    return res;
}

size_t UART_sendString(char* str) {
    size_t sizeStr;
    sizeStr = strlen(str);
    return UART_sendData((uint8_t* )str, sizeStr);
}

void UART_initBuffers(void) {
    rxBuffHandle = &g_rxBuff;
    txBuffHandle = &g_txBuff;
    RingBuffer_init(rxBuffHandle, g_receiveBuffer, UART_RX_BUFF_SIZE);
    RingBuffer_init(txBuffHandle, g_transmittBuffer, UART_TX_BUFF_SIZE);
}

__attribute__((isr)) void Uart0Handler(void) {
    if (UART_isEvent(UART_EVENT_RXDRDY) == true) {
        UART_clearEvent(UART_EVENT_RXDRDY);
        uint8_t data;
        UART_readRxd(&data);
        RingBuffer_put2(rxBuffHandle, data);
    }
    if (UART_isEvent(UART_EVENT_TXDRDY) == true) {
        UART_clearEvent(UART_EVENT_TXDRDY);
        uint8_t data;
        if ( RingBuffer_get(txBuffHandle, &data) == true ) {
            UART_writeTxd(data);
        }
    }
}
