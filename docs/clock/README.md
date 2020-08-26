###
nRF52840 has two clocks:
* high frequency (HF) 64 MHz clock
* low frequency (LF) 32.768 kHz clock

These clocks could be generated in differnt ways. \
HF clock could be generated using:
* on-chip oscilator
* external 32 MHz crystal.

However LF clock could be generated using:
* on-chip +/- 500ppm RC oscillator
* external 32.768 kHz crystal
* synthesized from 64 MHz oscillator

Clock control unit showed below:
![clock\_control](images/clock_control.png)

---

> Image is taken from [NordicSemiconductor](https://infocenter.nordicsemi.com) site.
> Any copyright belongs to NordicSemiconductors©


