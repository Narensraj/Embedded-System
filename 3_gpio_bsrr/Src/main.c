//GPIO output using Bit set/reset register


#include "stm32f4xx.h"

#define GPIOAEN 			(1U<<0) //GPIOA 0 register is set to 1
#define PIN5 				(1U<<5) //GPIOA pin 5 is set
#define LED_PIN				PIN5	//Defined pin 5 as led pin

int main(void)
{
	RCC->AHB1ENR |= GPIOAEN; 		//Clock is enabled for GPIOA

	/*To set the gpioa pin 5 as output*/
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	while(1)
	{
		GPIOA->BSRR = LED_PIN;		//Bit 5 is set to high(set)
		for(int i = 0; i<100000;i++)
		{

		}

		GPIOA->BSRR = (1U<<21);		//Bit 21 is set to high(reset)
		for(int i = 0; i<100000;i++)
		{

		}
	}
}
