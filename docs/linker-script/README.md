### Memory regions
nRF52840 FLASH memory region starts at address 0x00000000 and have size of 1M,
also its RAM region start at address 0x20000000 and have size of 256k.
FLASH is readable only and executable, but RAM is readable, writeable and executable.
So this will end up with the following memory region description in linker script:

### Memory model
![memory model](images/cortexM4_memory_model.png)

### Linker script

```
MEMORY {
	FLASH	(rx)	: ORIGIN = 0x00000000, 	LENGTH = 1M
	RAM	(rwx)	: ORIGIN = 0x20000000, 	LENGTH = 256K
}
```

Next we need to declare where code sections will be placed. This is done
by using SECTIONS directive. Most common section names are the following:
* **.text** - program code
* **.rodata** - read-only data
* **.data** - initialized global/static variables
* **.bss** - uninitialized global/static variables, which are zero
Also we need section to hold ISR vector table. Let it be:
* **.vectors** - interrupt service routine vector table
Section **.text**, **.rodata**, **.vectors** goes to FLASH memory and according to
ARMv7-M architecture, vector table is palced at the very beggining of FLASH memory
at address 0x00000000. And so sections **.data** and **.bss** goes to RAM memory.
But important note, due to harvard architecture and that RAM is volatile memory,
firstly we put these sections at FLASH and then copy to RAM at startup.\
We end up with:
```
SECTIONS {
	.vectors : AT (0x00000000) {
		. = ALIGN(4);		/* should be 4 byte alligned because of 32-bit memory organization */
		*(.vectors)
		. = ALIGN(4);
	} > FLASH

	.text : {
		. = ALIGN(4);
		*(.text*)
		*(.rodata*)
		. = ALIGN(4);
		_etext = .;
	} > FLASH
	
	.data : AT (_etext) {		/* AT specifies LMA, simply, at which address it is stored at FLASH*/
		. = ALIGN(4);
		_sdata = .;		/* Here we get VMA, simply, at which address is should be stored in RAM */
		*(.data*)
		. = ALIGN(4);
		_edata = .;
	} > RAM

	.bss : {
		. = ALIGN(4);
		_sbss = .;
		*(.bss*)
		. = ALIGN(4);
		_ebss = .;
	} > SRAM
}
```

---

> All information and images are taken from [NordicSemiconductors](https://infocenter.nordicsemi.com) site.
> Any copyright belongs to NordicSemiconductors©
