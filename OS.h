
#ifndef OS_OS_H_
#define OS_OS_H_

#include <stdint.h>

#define TASKS 3
#define NO_TASK 10
#define REGISTERS 8

extern uint8_t TASK_ACTIVE; //Guarda el indice de la lista de la tarea que esta en running

typedef enum{
	AUTOSTART_FALSE,
	AUTOSTART_TRUE
}Autostart;


typedef enum{
	NON_PREEMPTIVE,
	FULL_PREEMPTIVE
}SchedulingPolicy;

typedef enum{
	TASK_SUSPENDED,
	TASK_READY,
	TASK_RUNNING
}Task_State;


typedef uint8_t Task_Limit;
enum {
    TASK_DEACTIVATED,
    TASK_READY_TO_ACTIVATE,
    TASK_ACTIVATED
};

typedef enum{
		TASK_NCREATED,
		TASK_CREATED
}Task_Created;

typedef void (*TaskFunction)(void);

typedef struct{

	uint8_t task_ID;
	uint8_t priority;
	SchedulingPolicy Schedule;
	Task_Limit activation;
	Autostart autostart;
	TaskFunction task_ptr;
	Task_State state;
	Task_Created Task_Create;
	uint32_t *stackpointer;

}Task;

extern Task task_list[TASKS];

void OS_init(void);
void Activate_task(uint8_t task_ID);
void Terminate_task(void);
void Chain_task(uint8_t task_ID);
void Scheduler(void);
void Create_task(uint8_t Task_ID, uint8_t Priority, SchedulingPolicy Schedule, Autostart Autostart, TaskFunction Ptr_Task);
void SleepMode(void);

#endif /* OS_OS_H_ */
