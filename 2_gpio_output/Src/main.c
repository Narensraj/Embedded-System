//GPIO output using chip header


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
		GPIOA->ODR |= LED_PIN;		//Led is turned on
	}
}
