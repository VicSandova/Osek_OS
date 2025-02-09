
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "OS.h"


Task task_list[TASKS] = {0};

uint8_t TASK_ACTIVE = TASK_SUSPENDED;


void Create_task(uint8_t Task_ID, uint8_t Priority, SchedulingPolicy Schedule, Autostart Autostart, TaskFunction Ptr_Task) {
    for (int i = 0; i < TASKS; i++) {
        if (!task_list[i].Task_Create) {
            task_list[i].Task_Create = TASK_CREATED;
            task_list[i].task_ID = Task_ID;
            task_list[i].priority = Priority;
            task_list[i].Schedule = Schedule;
            task_list[i].activation = TASK_READY_TO_ACTIVATE;
            task_list[i].autostart = Autostart;
            task_list[i].task_ptr = Ptr_Task;
            task_list[i].state = TASK_SUSPENDED;
            //PRINTF("Tarea %d creada con prioridad %d\n", Task_ID, Priority);
            return;
        }
    }
    //PRINTF("Error: No hay espacio para más tareas\n");

}

void OS_init()
{

	/*
	 * Verificar que tareas tienen el autostart en TRUE para ejecutar activate_task(), de las que esten en true
	 */

	for(uint8_t i = 0;i < TASKS;i++){
		if(task_list[i].autostart == AUTOSTART_TRUE){
			task_list[i].state=TASK_READY;
		}
		else{
			task_list[i].state=TASK_SUSPENDED;
		}
	}
	//AJUSTAR SP
	Scheduler();

}

void Activate_task(uint8_t task_ID) {


	if((task_list[task_ID].activation == TASK_READY_TO_ACTIVATE) && (task_list[task_ID].state == TASK_SUSPENDED)){
		task_list[task_ID].state = TASK_READY;
		task_list[task_ID].activation = TASK_ACTIVATED;
	}
	else if(task_list[task_ID].state == TASK_READY){
		task_list[task_ID].state = TASK_READY;
	}
	else{
		task_list[task_ID].state = TASK_SUSPENDED;
		task_list[task_ID].activation = TASK_READY_TO_ACTIVATE;
	}


    Scheduler();  // Scheduler selects other task?

    //REVISAR STACKPOINTER FINAL Y AJUSTAR

    //ajustar el SP

}


void Terminate_task(){

    if(task_list[TASK_ACTIVE].state == TASK_READY && TASK_ACTIVE < TASKS){
    	task_list[TASK_ACTIVE].state = TASK_SUSPENDED;
    	task_list[TASK_ACTIVE].activation = TASK_READY_TO_ACTIVATE;
    }
    else{
    	//error
    }

    Scheduler();  // Scheduler selects other task?
}

void Chain_task(uint8_t task_ID){

    if(task_list[TASK_ACTIVE].state == TASK_READY && TASK_ACTIVE < TASKS){
    	task_list[TASK_ACTIVE].state = TASK_SUSPENDED;
    	task_list[TASK_ACTIVE].activation = TASK_READY_TO_ACTIVATE;
    }
    else{
    	//error;
    }

	if((task_list[task_ID].activation == TASK_READY_TO_ACTIVATE) && (task_list[task_ID].state == TASK_SUSPENDED)){
		task_list[task_ID].state = TASK_READY;
		task_list[task_ID].activation = TASK_ACTIVATED;
	}
	else if(task_list[task_ID].state == TASK_READY){
		task_list[task_ID].state = TASK_READY;
	}
	else{
		task_list[task_ID].state = TASK_SUSPENDED;
		task_list[task_ID].activation = TASK_READY_TO_ACTIVATE;
	}


    Scheduler();  // Scheduler selects other task?


	//TERMINAR LA TEREA ACTUAL en terminate/SUSPENDED
	//task id en ready
	//ajustar al stack
	//llamar scheduler

}

void Scheduler(){

    uint8_t highestPriorityTask = TASKS;
    uint8_t Highest_priority = 255;


    for (uint8_t i = 0; i < TASKS; i++) {

        if (task_list[i].state == TASK_READY && task_list[i].priority < Highest_priority) {
            Highest_priority = task_list[i].priority;
            highestPriorityTask = i;
        }
    }

    if (highestPriorityTask != TASKS) {
        task_list[highestPriorityTask].state = TASK_RUNNING;
        TASK_ACTIVE = highestPriorityTask;
        task_list[TASK_ACTIVE].task_ptr();
    }

	//verificar todas las tareas que esten en ready, ver cual tiene mayor prioridad para ponerla en running
	//ajustar el sp y apuntar a la task

}

