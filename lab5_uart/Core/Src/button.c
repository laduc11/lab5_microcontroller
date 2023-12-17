/*
 * button.c
 *
 *  Created on: Nov 7, 2023
 *      Author: DELL
 */

#include "button.h"

int counter[MAX_BUTTON];
uint8_t bFlag[MAX_BUTTON] = {0};
uint8_t bLongFlag[MAX_BUTTON] = {0};
arrState button[MAX_BUTTON];

/*Initial button state
 * input: none
 * output: none
 * */
void init_button_state()
{
	for (uint8_t i = 0; i < MAX_BUTTON; i++)
	{
		button[i].bState[0] = GPIO_PIN_SET;
		button[i].bState[1] = GPIO_PIN_SET;
		button[i].bState[2] = GPIO_PIN_SET;
		button[i].bState[3] = GPIO_PIN_SET;

		counter[i] = PRESS_TIME;
	}
}

/*
 * Check 3 nearest state of index button
 * input: index of button
 * output: state of button
 * */
uint8_t checkState(uint8_t idx)
{
	if (button[idx].bState[1] == GPIO_PIN_RESET && button[idx].bState[2] == GPIO_PIN_RESET && button[idx].bState[3] == GPIO_PIN_RESET)
		return GPIO_PIN_RESET;
	return GPIO_PIN_SET;
}

uint8_t isPressed(uint8_t idx)
{
	if (bFlag[idx] == 1)
	{
		bFlag[idx] = 0;
		return 1;
	}
	return 0;
}

uint8_t isLongPressed(uint8_t idx)
{
	if (bLongFlag[idx] == 1)
	{
		bLongFlag[idx] = 0;
		return 1;
	}
	return 0;
}

/*
 * Get input key
 * input: index of button
 * output: none
 * */
void getKey(uint8_t idx)
{
	button[idx].bState[1] = button[idx].bState[2];
	button[idx].bState[2] = button[idx].bState[3];
	button[idx].bState[3] = HAL_GPIO_ReadPin(BUTTON0_GPIO_Port, BUTTON0_Pin << idx);
	if (checkState(idx) == RESET)
	{
		if (button[idx].bState[0] == GPIO_PIN_SET)
		{
			// Debounced button
			bFlag[idx] = 1;
			button[idx].bState[0] = GPIO_PIN_RESET;
			counter[idx] = PRESS_TIME;
		}
		else
		{
			// Long pressed button
			if (counter[idx] == 0)
			{
				bLongFlag[idx] = 1;
				counter[idx] = PRESS_TIME;
			}
			else
			{
				counter[idx]--;
			}
		}
	}
	else
	{
		button[idx].bState[0] = GPIO_PIN_SET;
		counter[idx] = PRESS_TIME;
	}
}
