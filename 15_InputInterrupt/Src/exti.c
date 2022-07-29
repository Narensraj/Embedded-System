/*
 * exti.c
 *
 *  Created on: Jul. 26, 2022
 *      Author: Naren Subburaj
 */

#include "exti.h"

#define GPIOCEN			(1U<<3)
#define SYSCFGEN		(1U<<14)

void pc13_exti_init(void)
{
	/*Disable all global interrupt*/
	__disable_irq();

	/*Enable clock access or gpioc*/
	RCC->AHB1ENR |= GPIOCEN;

	/*PC13 as input*/
	GPIOC->MODER &=~ (1U<<26);
	GPIOC->MODER &=~ (1U<<27);

	/*Enable clock access for sysconfig*/
	RCC->APB2ENR |= SYSCFGEN;

	/*Select portc for exti*/
	SYSCFG->EXTICR[3] &=~(1u<<4);
	SYSCFG->EXTICR[3] |= (1u<<5);
	SYSCFG->EXTICR[3] &=~(1u<<6);
	SYSCFG->EXTICR[3] &=~(1u<<7);

	/*Unmask exti13*/
	EXTI->IMR |= (1U<<13);

	/*Select falling edge trigger*/
	EXTI->FTSR |= (1U<<13);

	/*Enable exti line for nvic*/
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	/*Enable global interrupt*/
	__enable_irq();

}
