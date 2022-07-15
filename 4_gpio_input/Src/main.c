//GPIO input driver


#include "stm32f4xx.h"

#define GPIOAEN 			(1U<<0) //GPIOA 0 register is set to 1
#define GPIOCEN				(1U<<2)	//GPIOC 2 register is set to 1

#define PIN5 				(1U<<5) //GPIOA pin 5 is set
#define PIN13				(1U<<13)//GPIOA pin 13 is set

#define LED_PIN				PIN5	//Defined pin 5 as led pin
#define BTN_PIN				PIN13	//Defined pin 13 as push button

int main(void)
{
	RCC->AHB1ENR |= GPIOAEN;		//Clock is enabled for GPIOA
	RCC->AHB1ENR |= GPIOCEN;		//Clock is enabled for GPIOC

	/*To set the gpioa pin 5 as output*/
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	/*To set the gpioc pin 13 as input*/
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);

	while(1)
	{
		if(GPIOC->IDR & BTN_PIN)	//If Input data register is true with Push button state
			GPIOA->BSRR = LED_PIN;

		else
			GPIOA->BSRR = (1U<<21);

	}
}
