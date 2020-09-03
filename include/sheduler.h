#ifndef SHEDULER_H
#define SHEDULER_H

#define MAX_NUM_TASKS 10

typedef int (*TaskEntry)(void);
typedef uint32_t shedtime_t;
typedef int pid_t;

pid_t addTaskSheduler(TaskEntry taskEntry, shedtime_t period);
int deleteTaskSheduler(pid_t pid);
int changeTaskPeriodSheduler(pid_t pid, shedtime_t period);
void runSheduler(void);
void tickShedulerTime(void);
shedtime_t getShedulerTime(void);

#endif  // SHEDULER_H
