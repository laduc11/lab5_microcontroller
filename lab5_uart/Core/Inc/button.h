/*
 * button.h
 *
 *  Created on: Nov 7, 2023
 *      Author: DELL
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define PRESS_TIME 300	// (*10ms)
#define MAX_BUTTON 1

typedef enum state
{
	NORMAL = 0,
	PRESSED = 1,
	LONG_PRESSED = 2
} STATE;
typedef struct arrGPIO
{
	GPIO_PinState bState[4];
} arrState;

void init_button_state();
uint8_t isPressed(uint8_t idx);
uint8_t isLongPressed(uint8_t idx);
void getKey(uint8_t idx);

#endif /* INC_BUTTON_H_ */
