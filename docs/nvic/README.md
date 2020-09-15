### Nested vectored interrupt controller (NVIC)
In nRF52840 SoC the NVIC supports 48 interrupts with 3 priority bits.
The NVIC and the processor core interface are closely coupled, to enable low
latency interrupt processing and efficient processing of late arriving interrupts.

Table of NVIC registers

|Address|Name|Description|
|:------|:---|:----------|
|0xE000E004|ICTR|Interrupt controller type register|
|0xE000E100 - 0xE000E11C|NVIC\_ISER[0..7]|Interrupt Set-Enable register|
|0xE000E180 - 0xE000E19C|NVIC\_ICER[0..7]|Interrupt Clear-Enable register|
|0xE000E200 - 0xE000E21C|NVIC\_ISPR[0..7]|Interrupt Set-Pending register|

//TODO complete table
