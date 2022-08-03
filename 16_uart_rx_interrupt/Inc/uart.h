/*
 * uart.h
 *
 *      Author: Naren subburaj
 */

#ifndef UART_H_
#define UART_H_

#include<stdio.h>
#include "stm32f4xx.h"
#include<stdint.h>

void uart_tx_init(void);
void led_blink(void);
char uart2_read(void);
void uart_rxtx_init(void);
void uart_rxtx_interrupt_init(void);

#endif /* UART_H_ */
