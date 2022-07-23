/*
 * Timer.h
 *
 *  Created on: Jul. 22, 2022
 *      Author: Naren Subburaj
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "stm32f4xx.h"

#define SR_UIF	(1U<<0)
void tim2_1hz_init(void);

#endif /* TIMER_H_ */
