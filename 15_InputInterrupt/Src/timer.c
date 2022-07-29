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

void tim2_pa5_output_compare(void)
{
	/*Enable clock for gpioa*/
	RCC->AHB1ENR |= (1U<<0);

	/*Set the gpioa to alternate function*/
	GPIOA->MODER &=~(1U<<10);
	GPIOA->MODER |= (1U<<11);

	/*Set the alternate function for timer 1 ch1 (af01)*/
	GPIOA->AFR[0] |= (1U<<20);
	GPIOA->AFR[0] &=~(1U<<21);
	GPIOA->AFR[0] &=~(1U<<22);
	GPIOA->AFR[0] &=~(1U<<23);

	/*Enable clock access for timer 2*/
	RCC->APB1ENR |= TIM2_EN;

	/*Set the prescaler value*/
	TIM2->PSC = 16000 - 1;

	/*Set the auto reload register value*/
	TIM2->ARR = 1000 - 1;

	/*Set output compare toggle mode*/
	TIM2->CCMR1 |= (1U<<4);
	TIM2->CCMR1 |= (1U<<5);
	TIM2->CCMR1 &=~(1U<<6);

	/*Enable timer 2 in compare capture mode*/
	TIM2->CCER |= (1U<<0);

	/*Clear the counter*/
	TIM2->CNT = 0;

	/*Enable the timer*/
	TIM2->CR1 |= (1U<<0);
}

void tim3_pa6_input_capture(void)
{
	/*Enable clock for gpioa*/
	RCC->AHB1ENR |= (1U<<0);

	/*Set the gpioa to alternate function*/
	GPIOA->MODER &=~(1U<<12);
	GPIOA->MODER |= (1U<<13);

	/*Set the alternate function for timer 1 ch1 (af02)*/
	GPIOA->AFR[0] &=~(1U<<24);
	GPIOA->AFR[0] |= (1U<<25);
	GPIOA->AFR[0] &=~(1U<<26);
	GPIOA->AFR[0] &=~(1U<<27);

	/*Enable clock access for timer 3*/
	RCC->APB1ENR |= (1U<<1);

	/*Set prescaler*/
	TIM3->PSC = 16000 - 1;

	/*Set ch1 to input mode*/
	TIM3->CCMR1 |= (1U<<0);
	TIM3->CCMR1 &=~(1U<<1);

	/*Set ch1 to capture at rising edge*/
	TIM3->CCER |= (1U<<0);

	/*Enable timer 3*/
	TIM3->CR1 |= (1U<<0);
}

