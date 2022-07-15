//Toggle the on board LED
//port : A
//pin : 5

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

#define RCC_AHB1ENR_offset			(0x30UL)
#define RCC_AHB1ENR_R				(*(volatile unsigned int *) (RCC_base + RCC_AHB1ENR_offset))

//Enable the GPIO A
#define GPIOAEN						(1U<<0)//shift 1 at position 0

#define GPIOA_MODER_offset			(0x00UL)
#define GPIOA_MODER_R				(*(volatile unsigned int *) (GPIO_base + GPIOA_MODER_offset))

//Make the gpio a as output register
#define GPIOA_ODR_offset			(0x14UL)
#define GPIOA_ODR_R					(*(volatile unsigned int *) (GPIO_base + GPIOA_ODR_offset))

#define PIN_5						(1U<<5)
#define LED							PIN_5



int main (void)
{

	RCC_AHB1ENR_R |= GPIOAEN;		//Set gpioaen register in rcc
	GPIOA_MODER_R |= (1U<<10);		//Set bit 10 as 1
	GPIOA_MODER_R &=~(1U<<11);		//Set bit 11 as 0



	while(1)
	{
		GPIOA_ODR_R ^= PIN_5;		//Toggle

		for(int i = 0 ; i<1000000 ; i++)
		{

		}
	}


}










