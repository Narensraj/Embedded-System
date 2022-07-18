//UART transmitter driver using printf

#include<stdio.h>
#include "stm32f4xx.h"
#include<stdint.h>

#define GPIOAEN 			(1U<<0) 			//GPIOA 0 register is set to 1
#define UART2EN				(1U<<17)			//Uart 2 : 17 bit is set to 1


#define SYS_freq			16000000			//System frequency 16MHZ
#define APB1_clk			SYS_freq
#define Uart_BaudRate		115200				//Set baud rate to 115200


void uart_tx_init(void);
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t Periphclk, uint32_t BaudRate);
static uint16_t uart_bd(uint32_t Periphclk, uint32_t BaudRate);
void uart2_write(int ch);
void led_blink(void);

/*put char function is used to return the unsigned character*/
int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}

/*uart2 write which sends the value into data register*/
void uart2_write(int ch)
{
	//Transmit data register is empty
	while(!(USART2->SR & (1U<<7))){}

	//write to transmit data register
	USART2->DR = (ch & 0xFF);
}

/*uart set baudrate whcih gets the value from the user and sets it to BRR*/
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t Periphclk, uint32_t BaudRate)
{
	USARTx->BRR = uart_bd(Periphclk,BaudRate);
}

/*uart bd which return the calculated periphclk and baudrate*/
static uint16_t uart_bd(uint32_t Periphclk, uint32_t BaudRate)
{
	return ((Periphclk + (BaudRate/2U))/BaudRate);
}

int main(void)
{
	uart_tx_init();								//UART transmit initialization


	while(1)
	{
		printf("This message is printed from stm32f411 \n\r");
		led_blink();							//led blink function
	}
}

/*LED blink function which makes the on board led PA5 toggle*/
void led_blink(void)
{
	GPIOA->ODR ^= (1U<<5);
	for(int i = 0; i<1000000; i++)
	{
	}
}

/*uart tx init where all the declaration are done*/
void uart_tx_init(void)
{
/*Configure gpioa pin*/
//Configure clock access
	RCC->AHB1ENR |= GPIOAEN;

//Configure pa5 as output led PA5
	GPIOA->MODER |=(1U<<10);
	GPIOA->MODER &=~(1U<<11);

//Configure alternate function for gpioa PA2
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);

//Configure alternate function to uart tx(af07)
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

//Uart clock access
	RCC->APB1ENR |= (1U<<17);

//Uart baudrate
	uart_set_baudrate(USART2, APB1_clk, Uart_BaudRate);

//Uart to set tx
	USART2->CR1 = (1U<<3);

//Uart enable
	USART2->CR1 |= (1U<<13);
}
