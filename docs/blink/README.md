### GPIO
To toggle LED on/off firstly we need to configure corresponding GPIO as output.
It is done by writing logical one to `A` field into corresponding
`PIN_CFN[n]` register. To drive pin high or low `OUTSET` or `OUTCLR` registers
are used. nRF52840 has two GPIO ports `P0` and `P1` with corresponding
base addresses `0x5000000` and `0x50000300` respectively. Register `PIN_CFN[n]`
offset could be derived as `0x700 + (n x 0x4 )`. Registers `OUTSET` and `OUTCLR`
offsets are `0x508` and `0x50C` respectively.
![instances](images/instances.png)
![registers\_1](images/registers_1.png)
![registers\_2](images/registers_2.png)

Searching in DK hardware schematics file we can see that leds are connected to
`P0.[13-16]` pins.
![gpio mapping](images/gpio_mapping.png)

Also it could be seen that leds are active low, meaning that when GPIO output
is low then led is turned ON. This is so called sink mode. In source mode action
is opposite.
![leds](images/leds.png)

To blink led1 `P0.13` should be used. Also for blink there is some sort of delay
routine is needed. For simplicity `for` loop is used.
```c
#include <stdint.h>
#include <gpio.h>

#define LOOP_COUNT 1000000

int main(void) {
	unsigned int LED1 = 13;
	
	GPIO_SET_DIR_OUT(gpio0, LED1);
	
	while (1) {
		GPIO_SET_HI(gpio0, LED1);
		for (int i = 0; i < LOOP_COUNT; i++) {
			;
		}
		GPIO_SET_LO(gpio0, LED1);
		for (int i = 0; i < LOOP_COUNT; i++) {
			;
		}
	}
}
```

GPIO is defined as memory mapped IO structure:

```c
typedef volatile struct __attribute__((packed)) {
	uint32_t reserved0[321];/* 0x000 - 0x500 reserved */
	uint32_t OUT;		/* 0x504 Write GPIO port */
	uint32_t OUTSET;	/* 0x508 Set individual bits in GPIO port */
	uint32_t OUTCLR;	/* 0x50C Clear individual bit in GPIO port */
	uint32_t IN;		/* 0x510 Read GPIO port */
	uint32_t DIR;		/* 0x514 Direction of GPIO port */
	uint32_t DIRSET;	/* 0x518 DIR set register */
	uint32_t DIRCLR;	/* 0x51C DIR clear register */
	uint32_t LATCH;		/* 0x520 Latch register indicating what GPIO pins
				   that have met the criteria set in the
				   PIN_CNF[n].SENSE registers*/
	uint32_t DETECTMODE;	/* 0x524 Select between default DETECT signal
				   behaviour and LDETECT mode*/
	uint32_t reserved1[118];/* 0x528 - 0x6FC reserved */
	uint32_t PIN_CNF[32];	/* 0x700 - 0x77C Configuration of GPIO pins*/
} GpioRegisters;

GpioRegisters* gpio0 = (GpioRegisters* )0x50000000u;
GpioRegisters* gpio1 = (GpioRegisters* )0x50000300u;
```

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
| [23:0]  | -         | Value to load into the `SYST_CVR` register      |

The `RELOAD` value can be any in the range `0x00000001 - 0x00FFFFFF`. A start
value of 0 is possible, but has no effect because the SysTick exception request
and `COUNTFLAG` are activated when counting from 1 to 0.

The `RELOAD` value is calculated according to its use. For example, to generate
a multi-shot timer with a period of N processor clock cycles, use `RELOAD` value
of N-1. If the SysTick interrupt is required every 100 clock pulses, set
`RELOAD` to 99.

---

> All information and images are taken from [NordicSemiconductors](https://infocenter.nordicsemi.com) site.
> Any copyright belongs to NordicSemiconductors©
