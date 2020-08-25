#include <stdint.h>
#include <stddef.h>
#include <systime.h>
#include <sheduler.h>

typedef struct {
	TaskEntry taskEntry;
	systime_t period;
	systime_t lastRun;
} TaskDescriptor;

static TaskDescriptor taskTable[MAX_NUM_TASKS] = { 0 };
static uint8_t tableIdx = 0;

ShedulerError addTaskSheduler(TaskEntry taskEntry, systime_t period) {
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
	while (1) {
		for (uint8_t i = 0; i < MAX_NUM_TASKS; i++) {
			TaskDescriptor* task = &taskTable[i];
			if (task->taskEntry == NULL) {
				continue;
			}

			if ( getSysTime() - task->lastRun >= task->period ) {
				task->lastRun = getSysTime();
				task->taskEntry();
			}
		}
	}
}
