### Memory regions
nRF52840 FLASH memory region starts at address 0x00000000 and have size of 1M,
also its RAM region start at address 0x20000000 and have size of 256k.

![memory model](images/cortexM4_memory_model.png)

FLASH is readable only and executable, but RAM is readable, writeable and
executable. So this will end up with the following memory region description in
linker script:

### Linker script
Firstly, we need to define microcontroller memory addresses, ex. `FLASH`, `RAM`.
This is done by using `MEMORY` directive.
Next we need to declare where code sections will be placed. This is done
by using `SECTIONS` directive. Most common section names are the following:
* `.text` - program code
* `.rodata` - read-only data
* `.data` - initialized global/static variables
* `.bss` - uninitialized global/static variables, which are zero
* `.preinit_array` and `.init_array` - contains arrays of pointers to
functions that will be called on initialization
* `.fini_array` - contains array of pointers to functions that will be
called on destruction

Also we need section to hold ISR vector table and stack pointer value.
Let it be:
* `.stack` - stack pointer value
* `.isr_vectors` - interrupt service routine vector table

1. Define the program entry point:
```
ENTRY(RESET_Handler)
```

2. Set up memory type, origin, length and access type:
```
MEMORY {
    FLASH   (rx) : ORIGIN = 0x00000000, LENGTH = 1M
    RAM    (rwx) : ORIGIN = 0x20000000, LENGTH = 256K
}
```

3. Set up section locations in memory:
```
SECTIONS {
    . = ORIGIN(FLASH);
    .text ALIGN(4) : {
        KEEP(*(.stack))
        KEEP(*(.exception_vectors))
        KEEP(*(.isr_vectors))
        *(.text)
        *(.text*)
        KEEP(*(.rodata*))
    } > FLASH
```

4. Place constructors and destructors sections:
```
    .preinit_array ALIGN(4) : {
        __preinit_array_start = .;
        KEEP(*(.preinit_array))
        KEEP(*(.preinit_array*))
        __preinit_array_end = .;
    } > FLASH

    .init_array ALIGN(4) : {
        __init_array_start = .;
        KEEP(*(.init_array))
        KEEP(*(.init_array*))
        __init_array_end = .;
    } > FLASH

    .fini_array ALIGN(4) : {
        __fini_array_start = .;
        KEEP(*(.fini_array))
        KEEP(*(.fini_array*))
        __fini_array_end = .;
    } > FLASH
```
At this point data stored in `FLASH` ends.

5. Define `__etext` symbol with address of code end:
```
    __etext = .;
```

6. Define stack top address, and data load address:
```
    /* according to ARM should be aligned to 8-byte border */
    __stacktop = ALIGN (ORIGIN(RAM) + LENGTH(RAM), 8);
    __data_load = LOADADDR(.data);
    . = ORIGIN(RAM);
```

7. Place `.data` section in `FLASH` but addresses are kept from `RAM` start(LMA,
VMA):
```
    .data ALIGN(4) : {
        __data_start = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        __data_end = .;
    } > RAM AT > FLASH
```

8. Similar place `.bss` section in `RAM`. Note this section does not consumes
space in `FLASH`, so we do not need to place it in `FLASH`. All we need are
`__bss_start` and `__bss_end` addresses:
```
    .bss ALIGN(4) (NOLOAD) : {
        __bss_start = .;
        *(.bss)
        *(.bss*)
        . = ALIGN(4);
        __bss_end = .;
        *(.noinit*)
    } > RAM
```

9. Define heap start address:
```
    . = ALIGN(4);
    __heap_start = .;
}
```

---

> All images are taken from [NordicSemiconductors](https://infocenter.nordicsemi.com) site.
