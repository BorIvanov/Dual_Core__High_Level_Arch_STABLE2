/*
 * vars.c
 *
 *  Created on: 6 Jun 2023
 *      Author: Boris Ivanov
 */

#include "level_2/vars.h"

void initGlobalVars(void)
{
	mem_Board[0] = 0; // board layout
	mem_Board[1] = 0; // board layout
	mem_Board[2] = 0; // board layout
	mem_Board[3] = 0; // board layout
	mem_Board[4] = 0; // board layout
	mem_Board[5] = 0; // board layout
	mem_Board[6] = 0; // board layout

	mem_Board_old[0] = 0; // board layout
	mem_Board_old[1] = 0; // board layout
	mem_Board_old[2] = 0; // board layout
	mem_Board_old[3] = 0; // board layout
	mem_Board_old[4] = 0; // board layout
	mem_Board_old[5] = 0; // board layout
	mem_Board_old[6] = 0; // board layout
}
