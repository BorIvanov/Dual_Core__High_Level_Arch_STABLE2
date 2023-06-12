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
#define STATE_ROBOT_MOVE					2
#define STATE_HUMAN_MOVE					3
#define STATE_CLEAN_UP						4
#define STATE_CHEAT_DETECTED				5
#define STATE_GAME_END						6

#define TASK_HUMAN_MOVE						0
#define TASK_ROBOT_MOVE						1
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
extern int state;



/* Functions */
void initGlobalVars();

#endif /* INC_VARS_H_ */
