### Cooperative sheduler
Cooperative sheduler is non-preemtive task manager. So, sheduler waits until
task ends and then gives CPU control to another task. Tasks could be choosen by
sheduler one after another or by selecting taks by time at which task wants to run.
System time is needed for sheduler. Every task needs description of its entry
point, and time period at which it wants to be executed.
```c
typedef struct {
    Sheduler_Task task;
    Sheduler_Pid pid;
    Sheduler_Time period;
    Sheduler_Time lastRun;
} Sheduler_TaskDescriptor;
```

`task` is pointer to task routine. It could return some value to indicate
some event happeded to sheduller, but for now nothing will be returned to
sheduler. \
So:
```c
typedef void (*Sheduler_Task)(void);
```
Also we need method to add tasks to sheduller:
```c
Sheduler_Pid Sheduler_addTask(Sheduler_Task task, Sheduler_Time period);
```
Here `Sheduler_Pid` is task process ID, if taks added successfully or is -1 if
addition to sheduler failed:

As we do not have dynamic memory allocation at the moment, we will use
static memory alocation for sheduler tasks. So we will specify how many
tasks sheduller will handle:
```c
#define MAX_NUM_TASKS 10
```
After tasks are set in sheduler, sheduler should be executed.
```c
void Sheduler_run(void);
```

All control routines over sheduler are listed below:
```c
typedef int (*Sheduler_Task)(void);
typedef uint32_t Sheduler_Time;
typedef int Sheduler_Pid;

Sheduler_Pid Sheduler_addTask(Sheduler_Task task, Sheduler_Time period);
int Sheduler_deleteTask(Sheduler_Pid pid);
int Sheduler_changeTaskPeriod(Sheduler_Pid pid, Sheduler_Time period);
void Sheduler_run(void);
void Sheduler_tickTime(void);
Sheduler_Time Sheduler_getTime(void);
```
