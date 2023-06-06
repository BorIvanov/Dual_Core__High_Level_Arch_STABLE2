/*
 * user_detector.c
 *	hardware device: PCA9554
 *
 *  Created on: Apr 24, 2023
 *      Author: Boris Ivanov
 */

#include "level_2/user_detector.h"

int coinInsertDetection(void)
/**
 * coinInsertDetection: check with light gates if coin is inserted
 *
 * returns:
 * 	0: no move
 * 	1-7: inserted into column n
 * 	9: error
 */
{
	int output = 0;

	/* Query the processor with the I2C connection for the light gates */
	int gateNew = queryLightGate();

	if (gateNew == 9)
	{
		detect_error++;
		return 9;
	}

	/* Query the logic: if the same as the prior gate, not debounced yet.  */
	if (gateNew == -1 && gateOld <= 7 && gateNew != gateOld)
	{
		output = gateOld;
	}

	gateOld = gateNew;

	return output;
}

int whatStackToFill(void)
/**
 * whatStackToFill: determine which storage stack to fill
 *
 * Always start filling the first stack, then the second, finally the last.
 * Each stack can hold max. 7 chips
 *
 * Returns:
 * 	-1: All stacks are full
 * 	0-2: Number of stack
 */
{
	int stack = 2;
	for (int i = 0; i < 3; i++) // loop through all options
	{
		if (mem_StorageStack[i] < 7) // assert if not filled
		{
			stack = i; // if not filled, use this stack
			break;
		}
	}
	return stack;
}

int whatStackToEmpty(void)
/**
 * whatStackToEmpty: determine which storage stack to empty
 *
 * Always start emptying the last stack, then the second, finally the first.
 *
 * Returns:
 * 	-1: All stacks are empty
 * 	0-2: Number of stack
 */
{
	int stack = 2;
	for (int i = 2; i >= 0; i--) // loop through all options
	{
		if (mem_StorageStack[i] > 0) // assert if not empty
		{
			stack = i; // if not empty, use this stack
			break;
		}
	}
	return stack;
}

void init_coinDetector(void)
{
	HAL_StatusTypeDef dev_Status;
	uint8_t data = 0xFF; // ensures all ports are INPUT configured

	// Program command byte:
	// configuration register [0x03] sets all ports as inputs (1)
	dev_Status = i2c_Transmit(&hi2c1, CD_ADD, 0x03, 1, &data, 1);

	if (dev_Status != HAL_OK) // if device is not OK
	{
		send_msg((uint8_t*) "\r¡User-Detector Initialisation FAILED¡\n\r");
		return;
	}
	else
	{
		send_msg((uint8_t*) "\r!User-Detector Initialised!\n\r");
	}
}

int queryLightGate(void)
/**
 * queryLightGate: read coin detector value.
 *
 * Reads coin detector using I2C. Returns column where something is present.
 *60000-1
 * Returns:
 * -2: Error from PCA9554
 * -1: All gates are free
 * 1-7: Stack where gate is blocked
 * 9: More than one gate is blocked
 */
{
	uint8_t cd;

	HAL_StatusTypeDef dev_Status;
	/* Retrieve input data from
	 * Single Registers:
	 0100 0001 - 0x41
	 0100 0011 - 0x43
	 0100 0101 - 0x45
	 0100 0111 - 0x47
	 0100 1001 - 0x49
	 0100 1011 - 0x4B
	 0100 1101 - 0x4D
	 0100 1111 - 0x4F
	 */
	// Program command byte: Reading the input port [0x00] register
	dev_Status = i2c_Receive(&hi2c1, CD_ADD, 0x00, 1, &cd, sizeof(cd));

	if (dev_Status != HAL_OK)
	{
		return -2;
	}
	else
	{
		/* Remove LSB: is always 1 */
		cd &= ~0x01;

		/* Check if empty: */
		if (!cd)
			return -1;

		if (cd == 0x02)
		{
			return 7;
		}
		if (cd == 0x04)
		{
			return 6;
		}
		if (cd == 0x08)
		{
			return 5;
		}
		if (cd == 0x10)
		{
			return 3; 	// flipped in hardware
		}
		if (cd == 0x20)
		{
			return 4; 	// flipped in hardware
		}
		if (cd == 0x40)
		{
			return 1; 	// flipped in hardware
		}
		if (cd == 0x80)
		{
			return 2; 	// flipped in hardware
		}

		//More than one coin
		if ((cd >> 1) & 1)
		{
			mem_Board[7 - 1]++;
		}
		if ((cd >> 2) & 1)
		{
			mem_Board[6 - 1]++;
		}
		if ((cd >> 3) & 1)
		{
			mem_Board[5 - 1]++;
		}
		if ((cd >> 4) & 1)
		{
			mem_Board[3 - 1]++;
		}
		if ((cd >> 5) & 1)
		{
			mem_Board[4 - 1]++;
		}
		if ((cd >> 6) & 1)
		{
			mem_Board[1 - 1]++;
		}
		if ((cd >> 7) & 1)
		{
			mem_Board[2 - 1]++;
		}
		sens = 0;
		return 9;
	}
}

/*Function to check if a new coin has been tossed in*/
int checkcoin(void)
{
	int column = -1;
	int amountOfColumnsChanged = 0;
	for (int i = 0; i < 7; i++)
	{
		if (mem_Board[i] - mem_Board_old[i] > 0)
		{
			column = i;
			amountOfColumnsChanged++;
		}
	}
	if (amountOfColumnsChanged == 1)
	{
		column++;
	}
	else if (amountOfColumnsChanged > 1)
	{
		column = 9;
	}
	return column;
}
