/*
 * Timer.h
 *
 *  Created on: Jul. 22, 2022
 *      Author: Naren Subburaj
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "stm32f4xx.h"

void tim2_1hz_init(void);
void tim2_pa5_output_compare(void);

#endif /* TIMER_H_ */
