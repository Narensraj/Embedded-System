//TImer for 1 second delay

#include "stm32f4xx.h"
#include<stdint.h>
#include "uart.h"
#include "systick.h"
#include "timer.h"

#define GPIOAEN 			(1U<<0) //GPIOA 0 register is set to 1
#define PIN5 				(1U<<5) //GPIOA pin 5 is set
#define LED_PIN				PIN5	//Defined pin 5 as led pin

int main(void)
{
	RCC->AHB1ENR |= GPIOAEN; 		//Clock is enabled for GPIOA

	/*To set the gpioa pin 5 as output*/
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	uart_rxtx_init();				//UART transceiver initialization
	tim2_1hz_init();

	while(1)
	{
		/*Check for UIF bit is set or not*/
		while(!(TIM2->SR & SR_UIF));

		/*Reset the UIF bit*/
		TIM2->SR &=~ SR_UIF;

		printf("A second is passed!\n\r");
		GPIOA->ODR ^= LED_PIN;
}
}


