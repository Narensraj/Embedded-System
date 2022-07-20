/*
 * uart.c
 *
 *      Author: Naren Subburaj
 */
#include "uart.h"


#define GPIOAEN 			(1U<<0) 			//GPIOA 0 register is set to 1
#define UART2EN				(1U<<17)			//Uart 2 : 17 bit is set to 1

#define CR1_TE				(1U<<3)
#define CR1_RE				(1U<<2)

#define CR1_UE				(1U<<13)
#define SR_TXE				(1U<<7)
#define SR_RXNE				(1U<<5)

#define SYS_freq			16000000			//System frequency 16MHZ
#define APB1_clk			SYS_freq
#define Uart_BaudRate		115200				//Set baud rate to 115200



static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t Periphclk, uint32_t BaudRate);
static uint16_t uart_bd(uint32_t Periphclk, uint32_t BaudRate);
void uart2_write(int ch);

/*put char function is used to return the unsigned character*/
int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}

/*LED blink function which makes the on board led PA5 toggle*/
void led_blink(void)
{
	GPIOA->ODR ^= (1U<<5);
	for(int i = 0; i<1000000; i++)
	{
	}
}


/*uart2 write which sends the value into data register*/
void uart2_write(int ch)
{
	//Transmit data register is empty
	while(!(USART2->SR & SR_TXE)){}

	//write to transmit data register
	USART2->DR = (ch & 0xFF);
}


char uart2_read(void)
{
	//Make sure the receive register is not empty
	while(!(USART2->SR & SR_RXNE)){}

	//Read data
	return USART2->DR;
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


/*uart tx init where all the declaration are done*/
void uart_rxtx_init(void)
{
/*Configure gpioa pin*/
//Configure clock access
	RCC->AHB1ENR |= GPIOAEN;

//Configure alternate function for gpioa PA2
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);


//Configure alternate function to uart tx(af07)
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

//Configure alternate function for gpioa PA3
	GPIOA->MODER &=~(1U<<6);
	GPIOA->MODER |= (1U<<7);

//Configure alternate function to uart tx(af07)
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &=~(1U<<15);

//Uart clock access
	RCC->APB1ENR |= UART2EN;

//Uart baudrate
	uart_set_baudrate(USART2, APB1_clk, Uart_BaudRate);

//Uart to set tx/rx
	USART2->CR1 = (CR1_TE | CR1_RE);



//Uart enable
	USART2->CR1 |= CR1_UE;
}
