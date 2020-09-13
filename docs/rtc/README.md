### Real time counter RTC
The Real-time counte (RTC) module provides a generic, low power timer on the
low-frequency clock source(LFCLK). The RTC module features a 24-bit `COUNTER`,
a 12-bit(1/X) prescaler, capture/compare registers, and a tick event generator
for low power, tickless RTOS implementation.

RTC block schematic:

![RTC block schematic](images/rtc_block_schematic.png)

The RTC will run off the LFCLK. The `COUNTER` resolution therefore will be
30.517 us. The software has to explicitely start LFCLK before using RTC.
Counter increment frequency is:
```
f_RTC [kHz] = 32.768 / ( PRESCALER + 1 )
```
Examples:
```
1.  Desired COUNTER frequency 100 Hz
    PRESCALER = round( 32.768 kHz / 100 Hz ) - 1 = 327
    f_RTC = 99.9 Hz
    10009.576 us counter period

2.  Desired COUNTER frequency 8 Hz
    PRESCALER = round( 32.768 kHz / 8 Hz ) - 1 = 4095
    f_RTC = 8 Hz
    125 ms counter period
```
| Prescaler | Counter resolution| Overflow       |
|:---------:|:-----------------:| -------------- |
| 0         | 30.517 us         | 512 seconds    |
| 2^8 - 1   | 7812.5 us         | 131072 seconds |
| 2^12 - 1  | 125 ms            | 582.542 hours  |

###### Overflow features
The `TRIGOVRFLW` task set the `COUNTER` calue to `0xFFFFF0` to allow software
test the overflow condition. Overflow occurs when `COUNTER` overflows from
`0xFFFFFF` to `0`. The `OVRFLW` event is disabled by default.

###### TICK event
The `TICK` event enables low poewr "tick-less" RTOS implementation as it
optionally privides a regular interrupt source for a RTOS without the need
to use ARM SysTick feature.
Using the RTC `TICK` event rather than the SysTick allows the CPU to be powered
down while still keeping RTOS sheduling active. The `TICK` event is disabled
by default.

###### Event control feature
To optimize RTC power consumption, events in RTC can be individually disabled
to prevent PCLK16M and HFCLK being requested when those events are triggered.
This is managed using the `EVTEN` register. \
For example, if the TICK event is not required for an application, this event
should be disabled as it is frequently occuring and may increase power
consumption if HFCLK otherwise could be powered down for long durations. \
