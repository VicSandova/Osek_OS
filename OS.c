
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_common.h"
#include "OS.h"
#include "DRIVERS/RGB_ticks.h"



Task task_list[TASKS] = {0};
uint8_t TASK_ACTIVE = NO_TASK;
uint32_t ptr; // Definir la variable en el archivo fuente

void SleepMode(void){

	SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;  // Configurar para Sleep (No Deep Sleep)
	__WFI();  // Esperar interrupción para despertar
	asm("ADD sp, sp, #0x04");

}


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
            task_list[i].ptr_context = NULL;

            //PRINTF("Tarea %d creada con prioridad %d\n", Task_ID, Priority);
            return;
        }
    }
    //PRINTF("Error: No hay espacio para más tareas\n");

}

void OS_init()
{

	for(uint8_t i = 0;i < TASKS;i++){
		if(task_list[i].autostart == AUTOSTART_TRUE){
			task_list[i].state=TASK_READY;
		}
		else{
			task_list[i].state=TASK_SUSPENDED;
		}
	}

	asm("ADD sp, sp, #0x10");
	//AJUSTAR SP
	Scheduler();

}

void Activate_task(uint8_t task_ID) {

	    asm("MOV R0, R14");
	    asm("SUB R0, R0, #1");
	    asm("LDR R1, =ptr");
	    asm("STR R0,[R1]");
	    task_list[TASK_ACTIVE].ptr_context=(void *)ptr;


	if((task_list[task_ID].activation == TASK_READY_TO_ACTIVATE) && (task_list[task_ID].state == TASK_SUSPENDED)){
		task_list[task_ID].state = TASK_READY;
		task_list[task_ID].activation = TASK_ACTIVATED;
	}
	else{
		task_list[task_ID].state = TASK_SUSPENDED;
		task_list[task_ID].activation = TASK_READY_TO_ACTIVATE;
	}

	asm("ADD sp,sp,#0x10");

    Scheduler();

    //REVISAR STACKPOINTER FINAL Y AJUSTAR

    //ajustar el SP

}


void Terminate_task(){

	task_list[TASK_ACTIVE].state = TASK_SUSPENDED;
	task_list[TASK_ACTIVE].activation = TASK_READY_TO_ACTIVATE;
	task_list[TASK_ACTIVE].ptr_context = NULL;
	TASK_ACTIVE = NO_TASK;

	Led_Off();
    asm("ADD sp, sp, #0x08");

    Scheduler();  // Scheduler selects other task?
}

void Chain_task(uint8_t task_ID){

    if(task_list[TASK_ACTIVE].state == TASK_RUNNING && TASK_ACTIVE < TASKS){
    	task_list[TASK_ACTIVE].state = TASK_SUSPENDED;
    	task_list[TASK_ACTIVE].activation = TASK_READY_TO_ACTIVATE;
    	task_list[TASK_ACTIVE].ptr_context = NULL;
    	TASK_ACTIVE = NO_TASK;
    	Led_Off();
    }
    else{
    	//error;
    }

	if((task_list[task_ID].activation == TASK_READY_TO_ACTIVATE) && (task_list[task_ID].state == TASK_SUSPENDED)){
		task_list[task_ID].state = TASK_READY;
		task_list[task_ID].activation = TASK_ACTIVATED;
	}
	else{
		task_list[task_ID].state = TASK_SUSPENDED;
		task_list[task_ID].activation = TASK_READY_TO_ACTIVATE;
	}

    asm("ADD sp, sp, #0x10");

    Scheduler();

	//ajustar al stack


}

void Scheduler() {
    asm("ADD sp, sp, #0x08");




    uint8_t highestPriorityTask = TASKS;
    uint8_t Highest_priority = 0;

    //  Buscar la tarea con la prioridad más alta en número
    for (uint8_t i = 0; i < TASKS; i++) {
        if (task_list[i].state == TASK_READY && task_list[i].priority > Highest_priority) {
            Highest_priority = task_list[i].priority;
            highestPriorityTask = i;
        }
    }

    //  Si no hay tareas listas, salir
    if (highestPriorityTask == TASKS) {
    	SleepMode();
        return;
    }

    //  Si ya está corriendo la tarea con mayor prioridad, no hacer cambio
    if (TASK_ACTIVE != NO_TASK && task_list[TASK_ACTIVE].priority >= task_list[highestPriorityTask].priority) {
        return;
    }

    //  Poner la tarea actual en READY si hay una activa
    if (TASK_ACTIVE != NO_TASK) {
        task_list[TASK_ACTIVE].state = TASK_READY;

    }

    //  Activar la nueva tarea con mayor prioridad
    task_list[highestPriorityTask].state = TASK_RUNNING;
    TASK_ACTIVE = highestPriorityTask;

    if(task_list[TASK_ACTIVE].ptr_context != NULL){
    	ptr = (int)task_list[TASK_ACTIVE].ptr_context;
        asm("ADD sp, sp, #0x10");  // 🔹 Ajuste del Stack Pointer si es necesario
    	asm("LDR R1, =ptr");
    	asm("LDR R0, [R1]");
    	asm("MOV PC, R0");
    }

    asm("ADD sp, sp, #0x10");  // 🔹 Ajuste del Stack Pointer si es necesario

    task_list[TASK_ACTIVE].task_ptr();
}
