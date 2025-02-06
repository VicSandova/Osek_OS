/*
 * OS.h
 *
 *  Created on: 3 feb. 2025
 *      Author: Eldic
 */

#ifndef OS_OS_H_
#define OS_OS_H_

#define TASKS 3



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

typedef void (*TaskFunction)(void);

typedef struct{

	uint8_t task_ID;
	uint8_t priority;
	SchedulingPolicy Schedule;
	uint8_t activation;
	Autostart autostart;
	TaskFunction task_ptr;
	Task_State state;
	bool Task_Created;

}Task;

extern Task task_list[TASKS];

void OS_init();
void Activate_task(uint8_t task_ID);
void Terminate_task();
void Chain_task(uint8_t task_ID);
void Scheduler();
void Create_task(uint8_t Task_ID, uint8_t Priority, SchedulingPolicy Schedule, Autostart Autostart, TaskFunction Ptr_Task);


#endif /* OS_OS_H_ */
