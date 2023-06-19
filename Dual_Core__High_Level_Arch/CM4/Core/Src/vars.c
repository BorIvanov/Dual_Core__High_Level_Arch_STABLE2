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
int state_flag = STATE_IDLE;
int current_state_CM4 = STATE_IDLE;
int previous_state_CM4 = -1;
bool continuous_robot_check = 1;
int played_column = 0;
double x_pos_array[] = { X_POS_COL_1, X_POS_COL_2, X_POS_COL_3, X_POS_COL_4, X_POS_COL_5, X_POS_COL_6, X_POS_COL_7 };

void initGlobalVars()
{

}

