#ifndef SHEDULER_H
#define SHEDULER_H

#include <systime.h>

#define MAX_NUM_TASKS 10

typedef void (*TaskEntry)(void);

typedef enum {
    SHEDULER_OK = 0,
    SHEDULER_TOO_MANY_TASKS
} ShedulerError;

ShedulerError addTaskSheduler(TaskEntry taskEntry, systime_t period);
void runSheduler(void);

#endif  // SHEDULER_H
