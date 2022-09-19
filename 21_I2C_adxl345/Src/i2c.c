/*
 * i2c.c
 *
 *  Created on: Aug 23, 2022
 *      Author: naren
 */

#include "i2c.h"

#define GPIOBEN			(1U<<1)
#define	I2CEN			(1U<<21)
#define I2C_100Khz		80		//Standard mode using (CCR = (Trscl + Twsclh)/Pclk1)
#define TRISE_MAX_RISE  17		//Calculated using (Trscl/Tpclk1 + 1)

/*Pin config
 *pb8 -> scl
 *pb9 -> sda
 * */
void i2c_init(void)
{
	/*Enable the clock access for the GPIOB*/
	RCC->AHB1ENR |= GPIOBEN;

	/*Set PB8 and PB9 to alternate function*/
	GPIOB->MODER |= (1U<<17);
	GPIOB->MODER &=~(1U<<16);

	GPIOB->MODER |= (1U<<19);
	GPIOB->MODER &=~(1U<<18);


	/*Set PB8 and PB9 output type to open drain*/
	GPIOB->OTYPER |= (1U<<8);
	GPIOB->OTYPER |= (1U<<9);

	/*Set PB8 and PB9 to PULLup*/
	GPIOB->PUPDR |= (1U<<16);
	GPIOB->PUPDR &=~(1U<<17);

	GPIOB->PUPDR |= (1U<<18);
	GPIOB->PUPDR &=~(1U<<19);

	GPIOB->AFR[1] &=~(1U<<3);//PB8
	GPIOB->AFR[1] |= (1U<<2);
	GPIOB->AFR[1] &=~(1U<<1);
	GPIOB->AFR[1] &=~(1U<<0);

	GPIOB->AFR[1] &=~(1U<<7);//PB9
	GPIOB->AFR[1] |= (1U<<6);
	GPIOB->AFR[1] &=~(1U<<5);
	GPIOB->AFR[1] &=~(1U<<4);

	/*Enable the clock access for i2c1*/
	RCC->APB1ENR |= I2CEN;

	/*Enter reset mode*/
	I2C1->CR1 |= (1U<<15);

	/*Come out of reset mode*/
	I2C1->CR1 &=~(1U<<15);

	/*Enter clock peripheral for i2c*/
	I2C1->CR2 |= (1U<<4);

	/*Set i2c clock speed as standard*/
	I2C1->CCR = (I2C_100Khz<<0);

	/*Set rise time*/
	I2C1->TRISE = TRISE_MAX_RISE;

	/*Enable i2c module*/
	I2C1->CR1 |= (1U<<0);
}

void I2C1_byteRead(char saddr, char maddr, char* data)
{
	volatile int temp;

	/*******To write*******/
	/*Wait until bus is not busy*/
	while(I2C1->SR2 & (1U<<1));

	/*Generate start*/
	I2C1->CR1 |= (1U<<8);

	/*Wait until start flag is set*/
	while(!(I2C1->SR1 & (1U<<0))){}

	/*Transmit the slave address + write*/
	I2C1->DR = saddr << 1;

	/*Wait until address flag is set*/
	while(!(I2C1->SR1 & (1U<<1))){}

	/*Clear the address flag*/
	temp = I2C1->SR1 | I2C1->SR2;

	/*Send memory address*/
	I2C1->DR = maddr;

	/*Wait until transmitter flag is empty*/
	while(!(I2C1->SR1 & (1U<<7))){}

	/*******To read********/
	/*Generate restart*/
	I2C1->CR1 |= (1U<<8);

	/*Wait until start flag is set*/
	while(!(I2C1->SR1 & (1U<<0))){}

	/*Transmit slave address + read*/
	I2C1->DR = saddr << 1 | 1;

	/*Wait until address flag is set*/
	while(!(I2C1->SR1 & (1U<<1))){}

	/*Disable acknowledge*/
	I2C1->CR1 &=~(1U<<10);

	/*Clear address flag*/
	temp = I2C1->SR1 | I2C1->SR2;

	/*Generate stop after data received*/
	I2C1->CR1 |= (1U<<9);

	/*Wait until RXNE flag is set*/
	while(!(I2C1->SR1 & (1U<<6))){}

	/*Read data from DR*/
	*data++ = I2C1->DR;
}

void I2C1_burstRead(char saddr, char maddr, int n, char* data)
{
	volatile int temp;

	/*Wait until bus is not busy*/
	while(I2C1->SR2 & (1U<<1)){}

	/*Generate start*/
	I2C1->CR1 |= (1U<<8);

	/*Wait until start flag is set*/
	while(!(I2C1->SR1 & (1U<<0))){}

	/*Transmit the slave address + write*/
	I2C1->DR = saddr << 1;

	/*Wait until address flag is set*/
	while(!(I2C1->SR1 & (1U<<1))){}

	/*Clear the address flag*/
	temp = I2C1->SR1 | I2C1->SR2;

	/*Wait until transmitter flag is empty*/
	while(!(I2C1->SR1 & (1U<<7))){}

	/*Send memory address*/
	I2C1->DR = maddr;

	/*Wait until transmitter flag is empty*/
	while(!(I2C1->SR1 & (1U<<7))){}

	/*Generate restart*/
	I2C1->CR1 |= (1U<<8);

	/*Wait until start flag is set*/
	while(!(I2C1->SR1 & (1U<<0))){}

	/*Transmit slave address + read*/
	I2C1->DR = saddr << 1 | 1;

	/*Wait until address flag is set*/
	while(!(I2C1->SR1 & (1U<<1))){}

	/*Clear address flag*/
	temp = I2C1->SR1 | I2C1->SR2;

	/*Enable acknowledge*/
	I2C1->CR1 |= (1U<<10);

	while(n > 0U)
	{
		/*If it reaches the last byte*/
		if(n == 1)
		{
			/*Disable acknowledge*/
			I2C1->CR1 &=~(1U<<10);

			/*Generate stop after data received*/
			I2C1->CR1 |= (1U<<9);

			/*Wait until RXNE flag is set*/
			while(!(I2C1->SR1 & (1U<<6))){}

			/*Read data from DR*/
			*data++ = I2C1->DR;
			break;
		}
		else
		{
			/*Wait until RXNE flag is set*/
			while(!(I2C1->SR1 & (1U<<6))){}

			/*Read data from DR*/
			*data++ = I2C1->DR;

			/*Decrement the n value*/
			n--;
		}
	}
}

void I2C1_burstWrite(char saddr, char maddr, int n, char* data)
{
	volatile int temp;

	/*Wait until bus is not busy*/
	while(I2C1->SR2 & (1U<<1)){}

	/*Generate start*/
	I2C1->CR1 |= (1U<<8);

	/*Wait until start flag is set*/
	while(!(I2C1->SR1 & (1U<<0))){}

	/*Transmit the slave address + write*/
	I2C1->DR = saddr << 1;

	/*Wait until address flag is set*/
	while(!(I2C1->SR1 & (1U<<1))){}

	/*Clear the address flag*/
	temp = I2C1->SR1 | I2C1->SR2;

	/*Wait until transmitter flag is empty*/
	while(!(I2C1->SR1 & (1U<<7))){}

	/*Send memory address*/
	I2C1->DR = maddr;

	for(int i = 0; i < n; i++)
	{
		/*Wait until transmitter flag is empty*/
		while(!(I2C1->SR1 & (1U<<7))){}

		/*Write data to DR*/
		I2C1->DR = *data++;
	}

	/*Wait until the transfer is complete*/
	while(!(I2C1->SR1 & (1U<<2))){}

	/*Generate stop after data received*/
	I2C1->CR1 |= (1U<<9);
}
