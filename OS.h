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
	bool autostart;
	TaskFunction task_ptr;
	Task_State state;
}Task;


void OS_init();
void Activate_task(uint8_t task_ID);
void Terminate_task();
void Chain_task(uint8_t task_ID);
void Scheduler();
void GetTask_ID(void *Task_ptr);
void GetTask_State(uint8_t task_ID,void *Task_ptr);
void Task_AF();
void Task_BF();
void Task_CF();

extern Task task_list[TASKS];

#endif /* OS_OS_H_ */
