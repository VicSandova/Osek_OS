
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "OS.h"


Task task_list[TASKS] = {0};


void Create_task(uint8_t Task_ID, uint8_t Priority, SchedulingPolicy Schedule, Autostart Autostart, TaskFunction Ptr_Task) {
    for (int i = 0; i < TASKS; i++) {
        if (!task_list[i].Task_Created) {
            task_list[i].Task_Created = true;
            task_list[i].task_ID = Task_ID;
            task_list[i].priority = Priority;
            task_list[i].Schedule = Schedule;
            task_list[i].activation = 1;
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
	//SCHEDULER


}

void Activate_task(uint8_t task_ID) {

    uint8_t runningTaskIndex = -1;
    uint8_t IDTaskIndex = -1;

    // Recorrer una sola vez la lista de tareas
    for (uint8_t i = 0; i < TASKS; i++) {
        if (task_list[i].state == TASK_RUNNING) {
            runningTaskIndex = i; // Guardar índice de la tarea en ejecución
        }
        if (task_list[i].task_ID == task_ID) {
        	IDTaskIndex = i;  // Guardar índice de la tarea a activar
        }

        // Si ya encontramos ambas tareas, salimos del for
        if (runningTaskIndex != -1 && IDTaskIndex != -1) {
            break;
        }
    }

    // Si hay una tarea en ejecución, cambiarla a READY
    if (runningTaskIndex != -1) {
        task_list[runningTaskIndex].state = TASK_READY;
    }

    // Si encontramos la tarea con `task_ID`, cambiar su estado
    if (IDTaskIndex != -1) {
        if (task_list[IDTaskIndex].state == TASK_SUSPENDED) {
            task_list[IDTaskIndex].state = TASK_READY;
        } else {
            task_list[IDTaskIndex].state = TASK_SUSPENDED; // Seguridad
        }
    }
    //Scheduler();  // Scheduler selects other task?


    //ajustar el SP


//    for(uint8_t i = 0; i < TASKS; i++){ //TASK RUNNING TO READY
//    	if(task_list[i].state == TASK_RUNNING){
//    		task_list[i].state = TASK_READY;
//    		break;
//    	}
//    }
//    for (uint8_t j = 0; j < TASKS; j++) { //TASK SUSPENED TO READY
//        if (task_list[j].task_ID == task_ID) {
//            if (task_list[j].state == TASK_SUSPENDED) {
//                task_list[j].state = TASK_READY;
//            } else {
//                task_list[j].state = TASK_SUSPENDED; //Other task state to suspended, security
//            }
//            return;
//        }
//    }



}


void Terminate_task(){

    for (uint8_t i = 0; i < TASKS; i++) {
        if (task_list[i].state == TASK_RUNNING) {  // Search for the task running
            task_list[i].state = TASK_SUSPENDED;
            return;
        }
    }
    //PRINTF("No task running to terminate!\n");

    //Scheduler();  // Scheduler selects other task?
}

void Chain_task(uint8_t task_ID){


	//TERMINAR LA TEREA ACTUAL en terminate/SUSPENDED
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


