//ADC for continuous conversion

#include "stm32f4xx.h"
#include<stdint.h>
#include "uart.h"
#include "adc.h"

uint32_t sensor_value;
int main(void)
{


	uart_rxtx_init();								//UART transceiver initialization
	pa1_adc_interrupt_int();
	start_conversion();
	while(1)
	{

}
}

static void adc_callback(void)
{
	sensor_value = ADC1->DR;
	printf("Sensor value : %d",(int)sensor_value);
}

void ADC_IRQHandler(void)
{
	/*Check for eoc in SR*/
	if((ADC1->SR & (1U<<1))!=0)
	{
		ADC1->SR &=~ (1U<<1);

		adc_callback();
	}
}

