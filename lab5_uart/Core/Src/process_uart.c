/*
 * process_uart.c
 *
 *  Created on: Dec 14, 2023
 *      Author: DELL
 */

#include "process_uart.h"

uint8_t buffer[MAX_BUFFER];
uint32_t indexBuffer;
uint8_t cmdRST, state;

/*
 * Initial start parameter for this module
 * Input: none
 * Output: none
 * */
void init_uart()
{
	state = 0;
	indexBuffer = 0;
	cmdRST = 0;
}

/*
 * Get input character form keyboard
 * Input: character
 * Output: none
 * */
void get_input(uint8_t character)
{
	if (indexBuffer >= MAX_BUFFER)
	{
		indexBuffer = 0;
	}

	buffer[indexBuffer] = character;
	indexBuffer++;
}

/*
 * Finite state machine for RST commnad
 * Input: state
 * Output: True or False
 * */
uint8_t fsm_RST()
{
	uint8_t done = 0;
	switch (state)
	{
	case 0:
		if (buffer[indexBuffer] == '!')
		{
			state++;
		}
		else
		{
			indexBuffer = 0;
		}
		break;
	case 1:
		if (buffer[indexBuffer] == 'R')
		{
			state++;
		}
		else
		{
			indexBuffer = 0;
			state = 0;
		}
		break;
	case 2:
		if (buffer[indexBuffer] == 'S')
		{
			state++;
		}
		else
		{
			indexBuffer = 0;
			state = 0;
		}
		break;
	case 3:
		if (buffer[indexBuffer] == 'T')
		{
			state++;
		}
		else
		{
			indexBuffer = 0;
			state = 0;
		}
		break;
	case 4:
		if (buffer[indexBuffer] == '#')
		{
			state = 0;
			cmdRST = 1;
			done = 1;
		}
		else
		{
			indexBuffer = 0;
			state = 0;
		}
		break;
	}
	return done;
}

/*
 * Finite state machine for RST command
 * Input: state
 * Output: True or False
 * */
uint8_t fsm_OK()
{
	uint8_t done = 0;
	switch (state)
	{
	case 0:
		if (buffer[indexBuffer] == '!')
		{
			state++;
		}
		else
		{
			indexBuffer = 0;
		}
		break;
	case 1:
		if (buffer[indexBuffer] == 'O')
		{
			state++;
		}
		else
		{
			indexBuffer = 0;
			state = 0;
		}
		break;
	case 2:
		if (buffer[indexBuffer] == 'K')
		{
			state++;
		}
		else
		{
			indexBuffer = 0;
			state = 0;
		}
		break;
	case 3:
		if (buffer[indexBuffer] == '#')
		{
			state = 0;
			cmdRST = 1;
			done = 1;
		}
		else
		{
			indexBuffer = 0;
			state = 0;
		}
		break;
	}
	return done;

}

/*
 * Process data in buffer
 * Input: none
 * Output: none
 * */
void proccess_buffer()
{
	if (cmdRST == 0 && state < 5)
	{
		fsm_RST(state);
	}
	else if (cmdRST == 1 && state < 4)
	{
		fsm_OK();
	}
	else
	{
		init_uart();
	}
}

/* Check the last command is RST or OK
 * Input: none
 * Output: True or False
 * */
uint8_t isRST()
{
	return cmdRST;
}


