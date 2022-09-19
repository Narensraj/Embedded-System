/*
 * i2c.h
 *
 *  Created on: Aug 23, 2022
 *      Author: naren
 */

#ifndef I2C_H_
#define I2C_H_

#include "stm32f4xx.h"
void i2c_init(void);
void I2C1_byteRead(char saddr, char maddr, char* data);
void I2C1_burstRead(char saddr, char maddr, int n, char* data);
void I2C1_burstWrite(char saddr, char maddr, int n, char* data);
#endif /* I2C_H_ */
