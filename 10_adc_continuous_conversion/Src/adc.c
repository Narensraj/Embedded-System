/*
 * adc.c
 *
 *  Created on: Jul. 20, 2022
 *      Author: Naren Subburaj
 */
#include"adc.h"

#define ADC1_EN 				(1U<<8)
#define GPIOA_EN				(1U<<0)
#define ADC1_CH1				(1U<<0)
#define ADC1_length				0x0000
#define ADC1_ON					(1U<<0)
#define SWSTART					(1U<<30)	//Start conversion
#define EOC						(1U<<1)		//End of conversion
#define ADC1_cont				(1U<<1)		//Enable continuous conversion

void pa1_adc_int(void)
{
	/*Enable clock access to PA1*/
	RCC->AHB1ENR |= GPIOA_EN;

	/*Configure MODER as analog*/
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	/*Enable clock access for ADC*/
	RCC->APB2ENR |= ADC1_EN;

	/*Configure adc parameters*/
	/*Conversion sequence start*/
	ADC1->SQR3 = ADC1_CH1;

	/*Conversion sequence length*/
	ADC1->SQR1 = ADC1_length;

	/*Enable ADC*/
	ADC1->CR2 |= ADC1_ON;
}

void start_conversion(void)
{
	/*Enable the continuous*/
	ADC1->CR2 |= ADC1_cont;

	/*start of the conversion*/
	ADC1->CR2 |= SWSTART;
}

uint32_t adc_read()
{
	/*Check whether the SR and eoc is true*/
	while(!(ADC1->SR & EOC)){
	}

	/*Return the data from data register*/
	return ADC1->DR;
}
