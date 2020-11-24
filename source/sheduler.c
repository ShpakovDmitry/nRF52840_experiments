#include <stdint.h>
#include <stddef.h>
#include <sheduler.h>

typedef struct {
    Sheduler_Task task;
    Sheduler_Pid pid;
    Sheduler_Time period;
    Sheduler_Time lastRun;
    Sheduler_Time nextRun;
} Sheduler_TaskDescriptor;

static const Sheduler_TaskDescriptor Sheduler_emptyTask = {
    .task = NULL,
    .pid = -1,
    .period = 0,
    .lastRun = 0,
    .nextRun = 0
};

static volatile Sheduler_Time shedtime;
static Sheduler_TaskDescriptor taskTable[SHEDULER_MAX_TASKS] = { 0 };

static int Sheduler_findFreeSpaceInTaskTable(void) {
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

static Sheduler_Pid Sheduler_addTaskGeneric(Sheduler_TaskDescriptor taskDescriptor) {
    int i;
    i = Sheduler_findFreeSpaceInTaskTable();
    if ( i == -1 ) {
        return -1;
    }

    Sheduler_Pid pid;
    pid = (Sheduler_Pid) i;    // pid is position in taskTable[]

    taskDescriptor.pid = pid;

    taskTable[i] = taskDescriptor;

    return pid;
}

Sheduler_Pid Sheduler_addTask(Sheduler_Task task, Sheduler_Time period) {
    Sheduler_TaskDescriptor taskToAdd;
    taskToAdd = Sheduler_emptyTask;
    taskToAdd.task = task;
    taskToAdd.period = period;
    return Sheduler_addTaskGeneric(taskToAdd);
}

int Sheduler_deleteTask(Sheduler_Pid pid) {
   int i;
   i = Sheduler_findPidInTaskTable(pid);
   if ( i == -1 ) {
        return -1;
   }
   Sheduler_TaskDescriptor* task = &taskTable[i];
   *task = Sheduler_emptyTask;

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

            if ( lastShedTime >= task->nextRun ) {
                if ( task->task() == -1 ) {
                    Sheduler_deleteTask(task->pid);
                    continue;
                }
                task->lastRun = lastShedTime;
                task->nextRun = lastShedTime + task->period;
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

Sheduler_Pid Sheduler_runTaskAt(Sheduler_Task task, Sheduler_Time time) {
    Sheduler_TaskDescriptor taskToAdd;
    taskToAdd = Sheduler_emptyTask;
    taskToAdd.task = task;
    taskToAdd.nextRun = time;
    return Sheduler_addTaskGeneric(taskToAdd);
}
