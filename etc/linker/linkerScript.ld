MEMORY {
	FLASH	(rx)	: ORIGIN = 0x00000000, 	LENGTH = 1M
	RAM	(rwx)	: ORIGIN = 0x20000000, 	LENGTH = 256K
}

stackTop = ALIGN (ORIGIN(RAM) + LENGTH(RAM), 8);
ENTRY(main)

SECTIONS {
	.vectors : AT (0x00000000) {
		. = ALIGN(4);		/* align on 32-bit border */
		KEEP(*(.vectors))
		. = ALIGN(4);
	} > FLASH

	.text : {
		. = ALIGN(4);
		*(.text*)
		*(.rodata*)
		. = ALIGN(4);
		_etext = .;
	} > FLASH
	
	.data : AT (_etext) {		/* AT specifies LMA */
		. = ALIGN(4);
		_sdata = .;		/* Here we get VMA */
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
        *(.noinit*)
	} > RAM
}

