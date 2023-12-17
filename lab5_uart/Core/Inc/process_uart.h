/*
 * process_uart.h
 *
 *  Created on: Dec 14, 2023
 *      Author: DELL
 */

#ifndef INC_PROCESS_UART_H_
#define INC_PROCESS_UART_H_

#include "main.h"
#include <stdio.h>

#define MAX_BUFFER 30

void get_input(uint8_t characteer);
void proccess_buffer();
uint8_t isRST();

#endif /* INC_PROCESS_UART_H_ */
