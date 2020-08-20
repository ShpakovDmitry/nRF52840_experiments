MEMORY {
	FLASH	(rx)	: ORIGIN = 0x00000000, 	LENGTH = 1M
	RAM	(rwx)	: ORIGIN = 0x20000000, 	LENGTH = 256K
}

stackTop = ALIGN (ORIGIN(RAM) + LENGTH(RAM), 8)

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

