### SysTime

To get out of `for` delay loop which is blocking, timer should be used. Timer
will lead to measurement of time intervals, so do tasks at desired time. nRF52840
gives 5x 32-bit Timers with counter mode and also system tick counter `SysTick`.
We could choose any of them. Here `SysTick` will be used. `SysTick` is 24-bit
timer thar counts down from the reload value to zero, reloads, that is wraps to,
the value in the `SYST_RVR` register on the next clock edge, then counts down
on subsequent clock register on the next clock edge, then counts down
on subsequent clocks.

> **NOTE**: When the processor is halted for debugging the counter does not
decrement

The system timer registers are:
| Address      | Name        | Type | Description                         |
|:-------------|:-----------:|:----:| ----------------------------------- |
| `0xE000E010` | SYST\_CSR   |  RW  | SysTick control and status register |
| `0xE000E014` | SYST\_RVR   |  RW  | SysTick reload value register       |
| `0xE000E018` | SYST\_CVR   |  RW  | SysTick current value register      |
| `0xE000E01C` | SYST\_CALIB |  RO  | SysTick calibration value register  |

The SysTick `SYST_CSR` register enables the SysTick features:
| Bits    | Name      | Function                                        |
|:-------:|:---------:| ----------------------------------------------- |
| [31:17] | -         | Reserved                                        |
| [16]    | COUNTFLAG | Returns 1 if timer counted to 0 since last read |
| [15:3]  | -         | Reserved                                        |
| [2]     | CLKSOURCE | Indicates the clock source                      |
|         |           | 0 = external clock                              |
|         |           | 1 = processor clock                             |
| [1]     | TICKINT   | Enables SysTick exception request               |
|         |           | 0 = does not assert the SysTick exception       |
|         |           | 1 = assert the SysTick exception                |
| [0]     | ENABLE    | Enables the counter                             |
|         |           | 0 = counter disabled                            |
|         |           | 1 = counter enabled                             |

When `ENABLE` is set to 1, the counter loads the `RELOAD` value from the
`SYST_RVR` register and then counts down. On reaching 0, it sets the `COUNTFLAG`
to 1 and optionally asserts the SysTick depending on the value of `TICKINT`.
It then loads the `RELOAD` value again, and begins counting.

The `SYST_RVR` register specifies the start value to load into the `SYST_CVR`
register.
| Bits    | Name      | Function                                        |
|:-------:|:---------:| ----------------------------------------------- |
| [31:24] | -         | Reserved                                        |
| [23:0]  | RELOAD    | Value to load into the `SYST_CVR` register      |

The `RELOAD` value can be any in the range `0x00000001 - 0x00FFFFFF`. A start
value of 0 is possible, but has no effect because the SysTick exception request
and `COUNTFLAG` are activated when counting from 1 to 0.

The `RELOAD` value is calculated according to its use. For example, to generate
a multi-shot timer with a period of N processor clock cycles, use `RELOAD` value
of N-1. If the SysTick interrupt is required every 100 clock pulses, set
`RELOAD` to 99.

The `SYST_CVR` register contains the current value of the SysTick counter.
| Bits    | Name      | Function                                        |
|:-------:|:---------:| ----------------------------------------------- |
| [31:24] | -         | Reserved                                        |
| [23:0]  | CURRENT   | Reads return the current value of the SysTick   |
|         |           | A write clears the field to 0, COUNTFLAG -> 0   |

The `SYST_CALIB` register indicates the SysTick calibration properties. The
reset value of this register is implemntation defined.
| Bits    | Name      | Function                                         |
|:-------:|:---------:| ------------------------------------------------ |
| [31]    | NOREF     | Indicates whether the device provides ref. clock |
|         |           | 0 = reference clock privided                     |
|         |           | 1 = no reference clock privided                  |
| [30]    | SKEW      | Indicates whether the TENMS value is exact       |
|         |           | 0 = TENMS value is exact                         |
|         |           | 1 = TENMS value is inexact, or not given         |
| [29:24] | -         | Reserved                                         |
| [23:0]  | TENMS     | Reload value for 10ms timing                     |

If calibration information is not known, calculate the calibration value
required from the frequency of the processor clock or external clock.

Some implementations stop all the processor clock signals during deep sleep
mode. If this happens, the SysTick counter stops.

Ensure software uses aligned word accesses to access the SysTick registers.

The SysTick counter reload and current value are not initialized by hardware.
This means the correct initialization sequence for the SysTick counter is:
1. Program reload value.
1. Clear current value.
1. Program control and status register.

After the SysTick is correctly initialized, it will handle exception `SysTick`
which is loaded from address `0x0000003C` to PC. So, correct handle routine
address should be placed there.

SysTime is encapsulated, so only throught defined routines access is gained to
it. They are:
```c
typedef uint32_t systime_t;

systime_t getSysTime(void);
void initSysTime(uint32_t reloadVal);
```
There is some predefined `RELOAD` values listed with self-described name:
```c
#define RELOAD_10MS_64MHZ 	0x09C3FF	//  10 ms @ 64 MHZ CPU clock
#define RELOAD_1MS_64MHZ 	0x00F9FF	//   1 ms @ 64 MHZ CPU clock
#define RELOAD_100US_64MHZ	0x0018FF	// 100 us @ 64 MHZ CPU clock
#define RELOAD_10US_64MHZ	0x00027F	//  10 us @ 64 MHZ CPU clock
#define RELOAD_1US_64MHZ	0x00003F	//   1 us @ 64 MHZ CPU clock
```

The SysTick interrupt priority could be set in `NMIC`, but by default it is `0`
as others exceptions and interrupts excluding `RESET = -3`, `NMI = -2`,
`HARD_FAULT = -1`. Low priority value means higher interrupt priority.
Interrupt with higher priority will preempt the interrupt with lower priority.
While handling the SysTick exception, its INT should be disabled.
```c
void SysTimeHandler(void) {
	disableSysTickInt();
	systime++;
	enableSysTickInt();
}
```
