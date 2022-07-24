//Timer input compare driver

#include "stm32f4xx.h"
#include<stdint.h>
#include "uart.h"
#include "systick.h"
#include "timer.h"

#define GPIOAEN 			(1U<<0) //GPIOA 0 register is set to 1
#define PIN5 				(1U<<5) //GPIOA pin 5 is set
#define LED_PIN				PIN5	//Defined pin 5 as led pin

int16_t timestamp = 0;

int main(void)
{
	RCC->AHB1ENR |= GPIOAEN; 		//Clock is enabled for GPIOA

	/*To set the gpioa pin 5 as output*/
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	uart_rxtx_init();								//UART transceiver initialization
	tim2_pa5_output_compare();
	tim3_pa6_input_capture();

	while(1)
	{
		/*Wait until edge is captured*/
		while(!(TIM3->SR & SR_CC1IF));

		/*Read captured value*/
		timestamp = TIM3->CCR1;

		printf("The time stamp value is %d\n\r",timestamp);

}
}


