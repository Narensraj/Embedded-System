/*
 * adc.h
 *
 *  Created on: Jul. 20, 2022
 *      Author: Naren Subburaj
 */

#ifndef ADC_H_
#define ADC_H_

#include "stm32f4xx.h"
#include<stdint.h>

void pa1_adc_int(void);
uint32_t adc_read();
void start_conversion(void);

#endif /* ADC_H_ */
