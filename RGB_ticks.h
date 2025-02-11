/*
 * RGB_ticks.h
 *
 *  Created on: 11 feb. 2025
 *      Author: Eldic
 */

#ifndef DRIVERS_RGB_TICKS_H_
#define DRIVERS_RGB_TICKS_H_

#include "stdint.h"

void RGB_ticks_Init();
void SysTick_Handler(void);
void Led_Red();
void Led_Blue();
void Led_Green();
void Led_Off();
void Led_White();
void SysTick_DelayTicks(uint32_t n);
void Duda();

#endif /* DRIVERS_RGB_TICKS_H_ */
