//Gpio interrupt driver

#include "stm32f4xx.h"
#include<stdint.h>
#include "uart.h"
#include "systick.h"
#include "timer.h"
#include "exti.h"

#define GPIOAEN 			(1U<<0) //GPIOA 0 register is set to 1
#define PIN5 				(1U<<5) //GPIOA pin 5 is set
#define LED_PIN				PIN5	//Defined pin 5 as led pin


int main(void)
{
	RCC->AHB1ENR |= GPIOAEN; 		//Clock is enabled for GPIOA

	/*To set the gpioa pin 5 as output*/
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	pc13_exti_init();
	uart_rxtx_init();

	while(1)
	{

}
}

static void exti_callback(void)
{
	printf("BTN pressed..\n\r");

	GPIOA->ODR ^= (1U<<5);
}

void EXTI15_10_IRQHandler(void)         			// EXTI Line[15:10] interrupts
{
	/*Check the pending register is set or not*/
	if((EXTI->PR & LINE13)!= 0)
	{
		EXTI->PR |= LINE13;
		exti_callback();
	}
}
