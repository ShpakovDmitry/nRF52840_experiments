/*
 *   file: scheduler.c
 * author: ShpakovDmitry
 *   date: 2021-11-16
 */

#include <stdint.h>
#include <stddef.h>
#include "scheduler.h"

typedef struct {
    Scheduler_Task task;
    Scheduler_Pid pid;
    Scheduler_Time period;
    Scheduler_Time lastRun;
    Scheduler_Time nextRun;
} Scheduler_TaskDescriptor;

static const Scheduler_TaskDescriptor Scheduler_emptyTask = {
    .task = NULL,
    .pid = -1,
    .period = 0,
    .lastRun = 0,
    .nextRun = 0
};

static volatile Scheduler_Time schedtime;
static Scheduler_TaskDescriptor taskTable[SCHEDULER_MAX_TASKS] = { 0 };

static int Scheduler_findFreeSpaceInTaskTable(void) {
    int i;
    for (i = 0; i < SCHEDULER_MAX_TASKS; i++) {
        if ( taskTable[i].task == NULL ) {
            break;
        }
    }

    return ( i == SCHEDULER_MAX_TASKS ? -1 : i);
}

static int Scheduler_findPidInTaskTable(Scheduler_Pid pid) {
    int i;
    for (i = 0; i < SCHEDULER_MAX_TASKS; i++) {
        if ( taskTable[i].pid == pid ) {
            break;
        }
    }

    return ( i == SCHEDULER_MAX_TASKS ? -1 : i);
}

static Scheduler_Pid Scheduler_addTaskGeneric(Scheduler_TaskDescriptor taskDescriptor) {
    int i;
    i = Scheduler_findFreeSpaceInTaskTable();
    if ( i == -1 ) {
        return -1;
    }

    Scheduler_Pid pid;
    pid = (Scheduler_Pid) i;    // pid is position in taskTable[]

    taskDescriptor.pid = pid;

    taskTable[i] = taskDescriptor;

    return pid;
}

Scheduler_Pid Scheduler_addTask(Scheduler_Task task, Scheduler_Time period) {
    Scheduler_TaskDescriptor taskToAdd;
    taskToAdd = Scheduler_emptyTask;
    taskToAdd.task = task;
    taskToAdd.period = period;
    return Scheduler_addTaskGeneric(taskToAdd);
}

int Scheduler_deleteTask(Scheduler_Pid pid) {
   int i;
   i = Scheduler_findPidInTaskTable(pid);
   if ( i == -1 ) {
        return -1;
   }
   Scheduler_TaskDescriptor* task = &taskTable[i];
   *task = Scheduler_emptyTask;

   return 0;
}

int Scheduler_changeTaskPeriod(Scheduler_Pid pid, Scheduler_Time period) {
    int i;
    i = Scheduler_findPidInTaskTable(pid);
    if ( i == -1 ) {
        return -1;
    }

    Scheduler_TaskDescriptor* task = &taskTable[i];
    task->period = period;
    
    return 0;
}

void Scheduler_run(void) {
    Scheduler_Time lastSchedTime = 0;
    Scheduler_Time currentSchedTime = 0;
    while (1) {
        currentSchedTime = Scheduler_getTime();
        if ( currentSchedTime == lastSchedTime ) {
            continue;
        }
        lastSchedTime = currentSchedTime;
        for (uint8_t i = 0; i < SCHEDULER_MAX_TASKS; i++) {
            Scheduler_TaskDescriptor* task = &taskTable[i];
            if (task->task == NULL) {
                continue;
            }

            if ( lastSchedTime >= task->nextRun ) {
                if ( task->task() == -1 ) {
                    Scheduler_deleteTask(task->pid);
                    continue;
                }
                task->lastRun = lastSchedTime;
                task->nextRun = lastSchedTime + task->period;
            }
        }
    }
}

void Scheduler_tickTime(void) {
    schedtime++;
}

Scheduler_Time Scheduler_getTime(void) {
    return schedtime;
}

Scheduler_Pid Scheduler_runTaskAt(Scheduler_Task task, Scheduler_Time time) {
    Scheduler_TaskDescriptor taskToAdd;
    taskToAdd = Scheduler_emptyTask;
    taskToAdd.task = task;
    taskToAdd.nextRun = time;
    return Scheduler_addTaskGeneric(taskToAdd);
}
