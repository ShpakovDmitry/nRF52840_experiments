#include <stdint.h>
#include <stddef.h>
#include <sheduler.h>

typedef struct {
    TaskEntry taskEntry;
    shedtime_t period;
    shedtime_t lastRun;
} TaskDescriptor;

static volatile shedtime_t shedtime;
static TaskDescriptor taskTable[MAX_NUM_TASKS] = { 0 };
static uint8_t tableIdx = 0;

ShedulerError addTaskSheduler(TaskEntry taskEntry, shedtime_t period) {
    if ( tableIdx >= MAX_NUM_TASKS ) {
        return SHEDULER_TOO_MANY_TASKS;
    }

    TaskDescriptor task = {
        .taskEntry = taskEntry,
        .period = period,
        .lastRun = 0
    };
    taskTable[tableIdx++] = task;

    return SHEDULER_OK;
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
