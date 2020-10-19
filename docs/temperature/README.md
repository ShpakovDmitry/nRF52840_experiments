### On board IC temperature sensor
The temperature sensor measures die temperature over the temperature range of
the device. Linearity compensation can be implemented if required by the
application. \
Listed here are the main features for `TEMP`:
* Temperature range is greated than or equal to operating temperature of the
device
* Resolution is 0.25 degrees.

`TEMP` is started by triggering the `START` task.
When the temperature measurement is completed, a `DATARDY` event will be
generated and the result of the measurement can be read from the `TEMP`
register.

To achieve the measurement accuracy stated in the electrical specification, the
crystal oscillator must be selected as the `HFCLK` source.
When the temperature measurement is completed, `TEMP` analog electronics power
down to save power.

`TEMP` only supports one-shot operation, meaning that every `TEMP` measurement
has to be explicitly started using the `START` task.

###### Registers

|Base address|Peripheral|Instance|Description                               |
|:-----------|:---------|:-------|:-----------------------------------------|
|0x4000C000  |TEMP      |TEMP    |Temperature sensor                        |

|Register       |Offset|Description                                             |
|:--------------|:----:|:----------                                             |
|TASKS\_START   |0x000 |Start temperature measurement                           |
|TASKS\_STOP    |0x004 |Stop temperature measurement                            |
|EVENTS\_DATARDY|0x100 |Temperature measurement complete, data ready            |
|INTENSET       |0x304 |Enable interrupt                                        |
|INTENCLR       |0x308 |Disable interrupt                                       |
|TEMP           |0x508 |Temperature in deg. Celsius (0.25 deg. steps)           |
|A0             |0x520 |Slope 1st piece wise linear function                    |
|A1             |0x524 |Slope 2st piece wise linear function                    |
|A2             |0x528 |Slope 3st piece wise linear function                    |
|A3             |0x52C |Slope 4st piece wise linear function                    |
|A4             |0x530 |Slope 5st piece wise linear function                    |
|A5             |0x534 |Slope 6st piece wise linear function                    |
|B0             |0x540 |y-intercept of 1st piece wise linear function           |
|B1             |0x544 |y-intercept of 2st piece wise linear function           |
|B2             |0x548 |y-intercept of 3st piece wise linear function           |
|B3             |0x54C |y-intercept of 4st piece wise linear function           |
|B4             |0x550 |y-intercept of 5st piece wise linear function           |
|B5             |0x554 |y-intercept of 6st piece wise linear function           |
|T0             |0x560 |End point of 1st piece wise linear function             |
|T1             |0x564 |End point of 2st piece wise linear function             |
|T2             |0x568 |End point of 3st piece wise linear function             |
|T3             |0x56C |End point of 4st piece wise linear function             |
|T4             |0x570 |End point of 5st piece wise linear function             |

###### Control methods
```c
void TEMP_startMeasure(void);
void TEMP_stopMeasure(void);
bool TEMP_isDataReady(void);
void TEMP_clearDataReady(void);
void TEMP_enableInterrupt(void);
void TEMP_disableInterrupt(void);
int32_t TEMP_getTemperature(void);
```
//TODO add description
