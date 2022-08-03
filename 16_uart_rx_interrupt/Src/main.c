//UART reciver driver using interrupt

#include "uart.h"

#define GPIOA_5		(1U<<5)
#define GPIOAEN		(1U<<0)

#define LED_pin		GPIOA_5

char key;
static void usart_callback(void);
void USART2_IRQHandler(void);

int main(void)
{

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	uart_rxtx_interrupt_init();					//UART transceiver interrupt initialization

	while(1)
	{
	}

}

static void usart_callback(void)
{
	key = USART2->DR;

	if(key == '1')
		GPIOA->ODR |= LED_pin;
	else
		GPIOA->ODR &=~ LED_pin;
}

void USART2_IRQHandler(void)
{
	if(USART2->SR & (1U<<5))
	{
		usart_callback();
	}
}
