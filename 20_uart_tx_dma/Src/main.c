//UART TX driver using DMA

#include "uart.h"

#define GPIOA_5		(1U<<5)
#define GPIOAEN		(1U<<0)

#define LED_pin		GPIOA_5

char key;
static void usart_callback(void);
void USART2_IRQHandler(void);

int main(void)
{

	char message[31] = "Hello from STM32 DMA transfer";
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	uart_rxtx_init();
	dma1_stream6_init((uint32_t) message, (uint32_t) &USART2->DR, 31);


	while(1)
	{
	}

}

static void usart_callback(void)
{
	GPIOA->ODR ^= LED_pin;
}

void DMA1_Stream6_IRQHandler(void)
{
	/*Check whether SR register is set or not*/
	if(DMA1->HISR & (1U<<21))
	{
		/*Clearing the SR register*/
		DMA1->HIFCR &=~(1U<<21);
		usart_callback();
	}
}
