/*
 * systick.c
 *
 *  Created on: Jul. 20, 2022
 *      Author: 15483
 */

#include"stm32f4xx.h"
#include"systick.h"

#define SYSTICK_LOAD_VAL 			16000
#define CTRL_ENABLE 				(1U<<0)
#define CTRL_CLKSRC					(1U<<2)
#define CTRL_COUNTFLAG				(1U<<16)

void systickDelayMs(int delay)
{
	/*Set load value as 16000 for 1ms*/
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	/*Clear systick current value*/
	SysTick->VAL = 0;

	/*Enable systick and select internal clock*/
	SysTick->CTRL = CTRL_CLKSRC;
	SysTick->CTRL |= CTRL_ENABLE;

	for(int i = 0; i < delay; i++)
	{
		/*Check for the count flag and systick control are true*/
		while(!(SysTick->CTRL & CTRL_COUNTFLAG)){
		}
	}
	SysTick->CTRL = 0;

}
