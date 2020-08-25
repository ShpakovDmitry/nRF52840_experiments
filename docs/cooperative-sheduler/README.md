### Cooperative sheduler
Cooperative sheduler is non-preemtive task manager. So, sheduler waits until
task ends and then gives CPU control to another task. Tasks could be choosen by
sheduler one after another or by selecting taks by time at which task wants to run.
System time is needed for sheduler. Every task needs description of its entry
point, and time period at which it wants to be executed.
```c
typedef struct {
	TaskEntry taskEntry;
	systime_t period;
	systime_t lastRun;
} TaskDescriptor;
```

`taskEntry` is pointer to task routine. It could return some value to indicate
some event happeded to sheduller, but for now nothing will be returned to
sheduler. \
So:
```c
typedef void (*TaskEntry)(void);
```

