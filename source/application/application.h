/*
 *   file: application.h
 * author: ShpakovDmitry
 *   date: 2020-12-18
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#ifdef __cplusplus
extern "C" {
#endif

void Application_run(void);

void Application_initHardware();
void Application_initScheduler();
void Application_runScheduler();
void Application_halt();
int Application_sendMessage(void);
int Application_blinkLed1(void);
int Application_blinkLed2(void);
int Application_blinkLed3(void);
int Application_blinkLed4(void);

#ifdef __cplusplus
}
#endif

#endif  // APPLICATION_H
