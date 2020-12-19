ENTRY(RESET_Handler)

MEMORY {
    FLASH   (rx) : ORIGIN = 0x00000000, LENGTH = 1M
    RAM    (rwx) : ORIGIN = 0x20000000, LENGTH = 256K
}

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

    __etext = .;

    /* according to ARM should be aligned to 8-byte border */
    __stacktop = ALIGN (ORIGIN(RAM) + LENGTH(RAM), 8);
    __data_load = LOADADDR(.data);
    . = ORIGIN(RAM);

    .data ALIGN(4) : {
        __data_start = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        __data_end = .;
    } > RAM AT > FLASH

    .bss ALIGN(4) (NOLOAD) : {
        __bss_start = .;
        *(.bss)
        *(.bss*)
        . = ALIGN(4);
        __bss_end = .;
        *(.noinit*)
    } > RAM

    . = ALIGN(4);
    __heap_start = .;
}
