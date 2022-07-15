//Toggle the on board LED using structure
//port : A
//pin : 5

#include<stdint.h>

//Peripheral base
#define PERIPH_base					(0x40000000UL)

//Bus base
#define AHB1_offset					(0x00020000UL)
#define AHB1_base					(PERIPH_base + AHB1_offset)

//Gpio port
#define GPIO_offset					(0x0000UL)
#define GPIO_base					(AHB1_base + GPIO_offset)

//Clock
#define RCC_offset					(0x3800UL)
#define RCC_base					(AHB1_base + RCC_offset)


//Enable the GPIO A
#define GPIOAEN						(1U<<0)						//shift 1 at position 0

#define PIN_5						(1U<<5)
#define LED							PIN_5

typedef struct{
	volatile uint32_t DUMMY[12];								//Bit manipulation
	volatile uint32_t AHB1ENR;									//RCC AHB1ENR register
}RCC_Typedef;

typedef struct{
	volatile uint32_t MODER; 									//GPIO port mode register
	volatile uint32_t DUMMY[4];									//Bit manipulation
	volatile uint32_t ODR;
}GPIO_Typedef;

#define RCC   ((RCC_Typedef*)RCC_base)
#define GPIOA  ((GPIO_Typedef*)GPIO_base)

int main (void)
{
		RCC->AHB1ENR |= GPIOAEN; 								//Clock is enabled for GPIOA

		/*To set the gpioa pin 5 as output*/
		GPIOA->MODER |= (1U<<10);
		GPIOA->MODER &=~(1U<<11);

	while(1)
	{
		GPIOA->ODR ^= PIN_5;									//Pin 5 is toggled

		for(int i = 0 ; i<1000000 ; i++)
		{

		}
	}
}
