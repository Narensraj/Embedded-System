/*
 * timer.c
 *
 *  Created on: Jul. 22, 2022
 *      Author: Naren Subburaj
 */
#include "timer.h"

#define TIM2_EN		(1U<<0)


void tim2_1hz_init(void)
{
	/*Enable clock access for timer 2*/
	RCC->APB1ENR |= TIM2_EN;

	/*Set the prescaler value*/
	TIM2->PSC = 16000 - 1;

	/*Set the auto reload register value*/
	TIM2->ARR = 1000 - 1;

	/*Clear the counter*/
	TIM2->CNT = 0;

	/*Enable the timer*/
	TIM2->CR1 |= (1U<<0);
}
