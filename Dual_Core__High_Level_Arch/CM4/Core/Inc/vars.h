/*
 * vars.h
 *
 *  Created on: Jun 6, 2023
 *      Author: Boris Ivanov
 */

#ifndef INC_VARS_H_
#define INC_VARS_H_

/* Defines */
#define NumberOfStorages 3
#define NumberOfBoardColumns 7
#define NumberOfBoardRows 6
//TODO: redefine
#define STATE_INIT							0
#define STATE_IDLE							1
#define STATE_ROBOT_TURN					2
#define STATE_USER_TURN					3
#define STATE_CLEAN_UP						4
#define STATE_CHEAT_DETECTED				5
#define STATE_GAME_END						6

#define TASK_USER_TURN						0
#define TASK_ROBOT_TURN						1
#define TASK_CLEAN_UP						2

/* Variables */
extern int mem_StorageStack[3];
extern int mem_Board[7];
extern int mem_Board_old[7];
extern int sens;
extern int Sens_CoinEntry;
extern int detect_error;	//coinDetect/input fails
extern int gateOld;			// Saves which gate the last thrown in coin was in.
extern int TIM7_CustomTimerCounter;
extern int state_flag;
extern int current_state;



/* Functions */
void initGlobalVars();

#endif /* INC_VARS_H_ */
