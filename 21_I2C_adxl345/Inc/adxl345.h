/*
 * adxl345.h
 *
 *  Created on: Sep. 11, 2022
 *      Author: naren
 */

#ifndef ADXL345_H_
#define ADXL345_H_

#include "i2c.h"

#define DEVID			(0x00)
#define DEVICE_ADDR 	(0x53)
#define DATA_FORMAT		(0x31)
#define POWER_CTL		(0x2D)
#define DATA_START_ADDR (0x32)

#define FOUR_G			(0x01)
#define RESET 			(0x00)
#define SET_MEASURE_B   (0x08)



void adxl_init (void);
void adxl_read_address (uint8_t reg);
void adxl_write(uint8_t reg, char value);
void adxl_read_values (uint8_t reg);

#endif /* ADXL345_H_ */
