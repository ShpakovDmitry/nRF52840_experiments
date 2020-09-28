#include <uart.h>
#include <stdint.h>

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

#define SET_BIT_HI(reg, bit) ( (reg) |=  (1 << (bit)) )
#define SET_BIT_LO(reg, bit) ( (reg) &= ~(1 << (bit)) )
#define GET_BIT(reg, bit)    ( (reg)  &  (1 << (bit)) )

void UART_startRx(void) {
    SET_BIT_HI(uart->TASKS_STARTRX, TASKS_STARTRX_BIT);
}
