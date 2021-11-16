/*
 *   file: scheduler.h
 * author: ShpakovDmitry
 *   date: 2021-11-16
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

#define SCHEDULER_MAX_TASKS 10

typedef int (*Scheduler_Task)(void);
typedef uint32_t Scheduler_Time;
typedef int Scheduler_Pid;

Scheduler_Pid Scheduler_addTask(Scheduler_Task task, Scheduler_Time period);
int Scheduler_deleteTask(Scheduler_Pid pid);
int Scheduler_changeTaskPeriod(Scheduler_Pid pid, Scheduler_Time period);
void Scheduler_run(void);
void Scheduler_tickTime(void);
Scheduler_Time Scheduler_getTime(void);
Scheduler_Pid Scheduler_runTaskAt(Scheduler_Task task, Scheduler_Time time);

#endif  // SCHEDULER_H
