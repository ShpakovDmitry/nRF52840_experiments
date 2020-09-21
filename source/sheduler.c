#include <stdint.h>
#include <stddef.h>
#include <sheduler.h>

typedef struct {
    Sheduler_Task task;
    Sheduler_Pid pid;
    Sheduler_Time period;
    Sheduler_Time lastRun;
} Sheduler_TaskDescriptor;

static volatile Sheduler_Time shedtime;
static Sheduler_TaskDescriptor taskTable[SHEDULER_MAX_TASKS] = { 0 };

static int Sheduler_findTaskInTaskTable(void) {
    int i;
    for (i = 0; i < SHEDULER_MAX_TASKS; i++) {
        if ( taskTable[i].task == NULL ) {
            break;
        }
    }

    return ( i == SHEDULER_MAX_TASKS ? -1 : i);
}

static int Sheduler_findPidInTaskTable(Sheduler_Pid pid) {
    int i;
    for (i = 0; i < SHEDULER_MAX_TASKS; i++) {
        if ( taskTable[i].pid == pid ) {
            break;
        }
    }

    return ( i == SHEDULER_MAX_TASKS ? -1 : i);
}

Sheduler_Pid Sheduler_addTask(Sheduler_Task task, Sheduler_Time period) {
    int i;
    i = Sheduler_findTaskInTaskTable();
    if ( i == -1 ) {
        return -1;
    }

    Sheduler_Pid pid;
    pid = (Sheduler_Pid) i;    // pid is position in taskTable[]

    Sheduler_TaskDescriptor taskToAdd = {
        .task = task,
        .pid = pid,
        .period = period,
        .lastRun = 0
    };

    taskTable[i] = taskToAdd;

    return pid;
}

int Sheduler_deleteTask(Sheduler_Pid pid) {
   int i;
   i = Sheduler_findPidInTaskTable(pid);
   if ( i == -1 ) {
        return -1;
   }
   Sheduler_TaskDescriptor* task = &taskTable[i];
   task->task = NULL;
   task->pid = -1;
   task->period = 0;
   task->lastRun = 0;

   return 0;
}

int Sheduler_changeTaskPeriod(Sheduler_Pid pid, Sheduler_Time period) {
    int i;
    i = Sheduler_findPidInTaskTable(pid);
    if ( i == -1 ) {
        return -1;
    }

    Sheduler_TaskDescriptor* task = &taskTable[i];
    task->period = period;
    
    return 0;
}

void Sheduler_run(void) {
    Sheduler_Time lastShedTime;
    while (1) {
        lastShedTime = Sheduler_getTime();
        for (uint8_t i = 0; i < SHEDULER_MAX_TASKS; i++) {
            Sheduler_TaskDescriptor* task = &taskTable[i];
            if (task->task == NULL) {
                continue;
            }

            if ( lastShedTime - task->lastRun >= task->period ) {
                task->lastRun = lastShedTime;
                if ( task->task() == -1 ) {
                    Sheduler_deleteTask(task->pid);
                }
            }
        }
    }
}

void Sheduler_tickTime(void) {
    shedtime++;
}

Sheduler_Time Sheduler_getTime(void) {
    return shedtime;
}
