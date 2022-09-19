/*
 * adxl345.c
 *
 *  Created on: Sep. 11, 2022
 *      Author: naren
 */

#include "adxl345.h"

char data;

uint8_t data_rec[6];

void adxl_read_address (uint8_t reg)
{
	I2C1_byteRead(DEVICE_ADDR , reg, &data);
}

void adxl_write(uint8_t reg, char value)
{
	char data[1];
	data[0] = value;
	I2C1_burstWrite(DEVICE_ADDR , reg, 1, data);
}

void adxl_read_values (uint8_t reg)
{
	I2C1_burstRead(DEVICE_ADDR, reg, 6, (char*) data_rec);
}

void adxl_init (void)
{
	i2c_init();

	/*Read the DEVID, this should return 0xE5*/
	adxl_read_address (DEVID);

	/*Set data format range to +-4g*/
	adxl_write(DATA_FORMAT, FOUR_G);

	/*Reset all bits*/
	adxl_write(POWER_CTL, RESET);

	/*Configure power control measure bit*/
	adxl_write(POWER_CTL, SET_MEASURE_B);
}
