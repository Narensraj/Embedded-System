//UART reciver driver

#include "stm32f4xx.h"
#include<stdint.h>
#include "uart.h"
#include "adc.h"

uint32_t sensor_value;
int main(void)
{


	uart_rxtx_init();								//UART transceiver initialization
	pa1_adc_int();
	start_conversion();
	while(1)
	{
		sensor_value = adc_read();
		printf("Sensor value : %d",(int)sensor_value);
}
}


