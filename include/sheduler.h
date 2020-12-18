#ifndef SHEDULER_H
#define SHEDULER_H

#include <stdint.h>

#define SHEDULER_MAX_TASKS 10

typedef int (*Sheduler_Task)(void);
typedef uint32_t Sheduler_Time;
typedef int Sheduler_Pid;

Sheduler_Pid Sheduler_addTask(Sheduler_Task task, Sheduler_Time period);
int Sheduler_deleteTask(Sheduler_Pid pid);
int Sheduler_changeTaskPeriod(Sheduler_Pid pid, Sheduler_Time period);
void Sheduler_run(void);
void Sheduler_tickTime(void);
Sheduler_Time Sheduler_getTime(void);
Sheduler_Pid Sheduler_runTaskAt(Sheduler_Task task, Sheduler_Time time);

#endif  // SHEDULER_H
