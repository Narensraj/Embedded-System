//UART transmitter driver using printf

#include "uart.h"

int main(void)
{
	uart_tx_init();								//UART transmit initialization


	while(1)
	{
		printf("This message is printed from stm32f411 \n\r");
		led_blink();							//led blink function
	}
}


