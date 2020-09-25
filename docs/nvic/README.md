### Nested vectored interrupt controller (NVIC)
In nRF52840 SoC the NVIC supports 48 interrupts with 3 priority bits.
The NVIC and the processor core interface are closely coupled, to enable low
latency interrupt processing and efficient processing of late arriving interrupts.

Table of NVIC registers

|Address                |Name            |Description                       |
|:----------------------|:---------------|:---------------------------------|
|0xE000E004             |ICTR            |Interrupt controller type register|
|0xE000E100 - 0xE000E11C|NVIC\_ISER[0..7]|Interrupt Set-Enable register     |
|0xE000E180 - 0xE000E19C|NVIC\_ICER[0..7]|Interrupt Clear-Enable register   |
|0xE000E200 - 0xE000E21C|NVIC\_ISPR[0..7]|Interrupt Set-Pending register    |
|0xE000E280 - 0xE000E29C|NVIC\_ICPR[0..7]|Interrupt Clear-Pending register  |
|0xE000E300 - 0xE000E31C|NVIC\_IABR[0..7]|Interrupt Active Bit register     |
|0xE000E400 - 0xE000E4EC|NVIC\_IPR[0..7] |Interrupt Priority register       |

Control over NVIC is done by following routines:
```c
void NVIC_enableGlobalIrq(void);
void NVIC_disableGlobalIrq(void);

void NVIC_enableIrq(IrqNvic irqNvic);
void NVIC_disableIrq(IrqNvic irqNvic);
void NVIC_setPendingIrq(IrqNvic irqNvic);
void NVIC_clearPendingIrq(IrqNvic irqNvic);
bool NVIC_isPendingIrq(IrqNvic irqNvic);
void NVIC_setPriorityIrq(IrqNvic irqNvic, uint8_t priority);
```

To set any peripheral interrupt to be active the following should be done:
* set enable interrupt bit in periphery register
* set enable interrupt bit in NVIC
* enable global interrupts by calling `NVIC_enableGlobalIrq()`

Also, interrupt handler should be written. By default there is a `weak`
connection to `DummyInterrupt()` routine. To use own interrupt handler simple
write the routine with the same name as appropriate interrupt routine name
declared in `source/isr.c` file.
When entering the interrupt service routine(ISR) the following should be done:
* As there may be more than one interrupt source for periphery, in ISR there
need to be checked which event were generated and then execute appropriate
code path.
* clear the generated interrupt event in periphery registers. This is to not
call the same interrupt after the ISR routine is exited.

Every ISR should be added `isr` attribute, for example:
```c
__attribute__((isr)) void Rtc0Handler(void) {
    // check which event generated interrupt
    // clear this event
    // ISR code here
}
```

Also to get full description about NVIC, please refer to ARM Cortex-M4 manual.
