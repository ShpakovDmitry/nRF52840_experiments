#include <stdint.h>
#include <stddef.h>
#include <sheduler.h>

typedef struct {
    TaskEntry taskEntry;
    pid_t pid;
    shedtime_t period;
    shedtime_t lastRun;
} TaskDescriptor;

static volatile shedtime_t shedtime;
static TaskDescriptor taskTable[MAX_NUM_TASKS] = { 0 };

static int findTaskInTaskTable(void) {
    int i;
    for (i = 0; i < MAX_NUM_TASKS; i++) {
        if ( taskTable[i].taskEntry == NULL ) {
            break;
        }
    }

    return ( i == MAX_NUM_TASKS ? -1 : i);
}

static int findPidInTaskTable(pid_t pid) {
    int i;
    for (i = 0; i < MAX_NUM_TASKS; i++) {
        if ( taskTable[i].pid == pid ) {
            break;
        }
    }

    return ( i == MAX_NUM_TASKS ? -1 : i);
}

pid_t addTaskSheduler(TaskEntry taskEntry, shedtime_t period) {
    int i;
    i = findTaskInTaskTable();
    if ( i == -1 ) {
        return -1;
    }

    pid_t pid;
    pid = (pid_t) i;    // pid is position in taskTable[]

    TaskDescriptor task = {
        .taskEntry = taskEntry,
        .pid = pid,
        .period = period,
        .lastRun = 0
    };

    taskTable[i] = task;

    return pid;
}

int deleteTaskSheduler(pid_t pid) {
   int i;
   i = findPidInTaskTable(pid);
   if ( i == -1 ) {
        return -1;
   }
   TaskDescriptor* task = &taskTable[i];
   task->taskEntry = NULL;
   task->pid = -1;
   task->period = 0;
   task->lastRun = 0;

   return 0;
}

int changeTaskPeriodSheduler(pid_t pid, shedtime_t period) {
    int i;
    i = findPidInTaskTable(pid);
    if ( i == -1 ) {
        return -1;
    }

    TaskDescriptor* task = &taskTable[i];
    task->period = period;
    
    return 0;
}

void runSheduler(void) {
    shedtime_t lastShedTime;
    while (1) {
        lastShedTime = getShedulerTime();
        for (uint8_t i = 0; i < MAX_NUM_TASKS; i++) {
            TaskDescriptor* task = &taskTable[i];
            if (task->taskEntry == NULL) {
                continue;
            }

            if ( lastShedTime - task->lastRun >= task->period ) {
                task->lastRun = lastShedTime;
                task->taskEntry();
            }
        }
    }
}

void tickShedulerTime(void) {
    shedtime++;
}

shedtime_t getShedulerTime(void) {
    return shedtime;
}
