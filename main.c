
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "OS/OS.h"

void Task_AF();
void Task_BF();
void Task_CF();


int main(void) {

	Create_task(0, 1, FULL_PREEMPTIVE, AUTOSTART_TRUE, Task_AF);
	Create_task(1, 2, FULL_PREEMPTIVE, AUTOSTART_FALSE, Task_BF);
	Create_task(2, 3, FULL_PREEMPTIVE, AUTOSTART_TRUE, Task_CF);


	OS_init();

	while(1){


	/*el scheduler se llama despues de terminar o iniciar una tarea?
	 * quien pone a la tarea en running?
	 *
	 */

	}

}


void Task_AF(){
	//stackp 1 guardas sp
	Activate_task(1);//comparar el valor del stackpointer del main con el de la funcion
	//Guardar dirección de retorno, guardar el PC
	Terminate_task();

}//nunca se ejecuta la llave

void Task_BF(){

	Chain_task(2);

}//nunca se ejecuta la llave

void Task_CF(){

	Terminate_task();

}//nunca se ejecuta la llave

//
//Task task_list[TASKS] = {
//		{0, 1, FULL_PREEMPTIVE, 1, true, Task_AF, TASK_SUSPENDED}, //TASK_ID, PRIORITY, SCHEDULE, ACTIVATION, AUTOSTART, TASK_PTR, TASK_STATE
//		{1, 2, FULL_PREEMPTIVE, 1, false, Task_BF, TASK_SUSPENDED}, //Mover a private estado de tarea
//		{2, 3, FULL_PREEMPTIVE, 1, true, Task_CF, TASK_SUSPENDED}
//};//&task_A
////O DECLARE TASK???
