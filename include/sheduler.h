#ifndef SHEDULER_H
#define SHEDULER_H

#define MAX_NUM_TASKS 10

typedef void (*TaskEntry)(void);
typedef uint32_t shedtime_t;

typedef enum {
    SHEDULER_OK = 0,
    SHEDULER_TOO_MANY_TASKS
} ShedulerError;

ShedulerError addTaskSheduler(TaskEntry taskEntry, shedtime_t period);
void runSheduler(void);
void tickShedulerTime(void);
shedtime_t getShedulerTime(void);

#endif  // SHEDULER_H
