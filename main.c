#include "fsl_smc.h"
#include "fsl_clock.h"
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
	Create_task(2, 3, FULL_PREEMPTIVE, AUTOSTART_FALSE, Task_CF);

	OS_init();

	while(1){

		SleepMode();
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

