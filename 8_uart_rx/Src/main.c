//UART reciver driver

#include "uart.h"

#define GPIOA_5		(1U<<5)
#define GPIOAEN		(1U<<0)

#define LED_pin		GPIOA_5

char key;

int main(void)
{

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	uart_rxtx_init();								//UART transceiver initialization

	while(1)
	{
		key = uart2_read();

		if(key == '1')
			GPIOA->ODR |= LED_pin;
		else
			GPIOA->ODR &=~ LED_pin;
	}

}


