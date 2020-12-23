/*
 *   file: Target_nRF52840.h
 * author: ShpakovDmitry
 *   date: 2020-12-18
 */

#ifndef TARGET_NRF52840_H
#define TARGET_NRF52840_H

typedef struct THardware_nRF52840 {
    void (*const init)(void);
    void (*const puts)(char* );

} THardware_nRF52840;

typedef THardware_nRF52840 * THardware_nRF52840_Handle;

void nRF52840_ctor(THardware_nRF52840_Handle * me);

//void nRF52840_init();
//void nRF52840_puts(char* str);

#endif  // TARGET_NRF52840_H
