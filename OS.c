
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "OS.h"

	Task task_list[TASKS] = {
			{0, 1, FULL_PREEMPTIVE, 1, true, Task_AF, TASK_SUSPENDED}, //TASK_ID, PRIORITY, SCHEDULE, ACTIVATION, AUTOSTART, TASK_PTR, TASK_STATE
			{1, 2, FULL_PREEMPTIVE, 1, false, Task_BF, TASK_SUSPENDED},
			{2, 3, FULL_PREEMPTIVE, 1, true, Task_CF, TASK_SUSPENDED}
	};//&task_A
//O DECLARE TASK???


void OS_init()
{

}

void Activate_task(uint8_t task_ID) {

    for(uint8_t i = 0; i < TASKS; i++){ //TASK RUNNING TO READY
    	if(task_list[i].state == TASK_RUNNING){
    		task_list[i].state = TASK_READY;
    		break;
    	}
    }
    for (uint8_t j = 0; j < TASKS; j++) { //TASK SUSPENED TO READY
        if (task_list[j].task_ID == task_ID) {
            if (task_list[j].state == TASK_SUSPENDED) {
                task_list[j].state = TASK_READY;
            } else {
                task_list[j].state = TASK_SUSPENDED; //Other task state to suspended, security
            }
            return;
        }
    }
    //Scheduler();  // Scheduler selects other task?


    //ajustar el SP


}


void Terminate_task(){

    for (uint8_t i = 0; i < TASKS; i++) {
        if (task_list[i].state == TASK_RUNNING) {  // Search for the task running
            task_list[i].state = TASK_SUSPENDED;
            return;
        }
    }
    PRINTF("No task running to terminate!\n");

    //Scheduler();  // Scheduler selects other task?
}

void Chain_task(uint8_t task_ID){


	//TERMINAR LA TEREA ACTUAL en terminate
	//task id en ready
	//ajustar al stack
	//llamar scheduler

}

void Scheduler(){

	//verificar todas las tareas que esten en ready, ver cual tiene mayor prioridad para ponerla en running
	//ajustar el sp y apuntar a la task

}

void GetTask_ID(void *Task_ptr){

}

void GetTask_State(uint8_t task_ID,void *Task_ptr){

}

void Task_AF(){

	Activate_task(1);
	Terminate_task();

}

void Task_BF(){

	Chain_task(2);

}

void Task_CF(){

	Terminate_task();

}
