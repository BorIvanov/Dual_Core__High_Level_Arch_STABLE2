/*
 * vars.c
 *
 *  Created on: Jun 6, 2023
 *      Author: Boris Ivanov
 */

#include "vars.h"

int mem_StorageStack[3];
int mem_Board[7];
int mem_Board_old[7];
int sens;
int Sens_CoinEntry = 0;
int detect_error = 0;	//coinDetect/input fails
int gateOld = -1;
int TIM7_CustomTimerCounter = 0;
int state = STATE_IDLE;

void initGlobalVars()
{

}

