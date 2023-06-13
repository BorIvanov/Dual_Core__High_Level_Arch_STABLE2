/*
 * task_generator.h
 *
 *  Created on: Apr 24, 2023
 *      Author: Boris Ivanov
 *
 *  Description: Generates tasks for C-M4, based on the state of the Game Controller (GC).
 *  Based on the tasks C-M4 will react differently.
 */

#ifndef INC_LEVEL_2_TASK_GENERATOR_H_
#define INC_LEVEL_2_TASK_GENERATOR_H_

#include "main.h"
#include <string.h>
#include "D:\University\Fontys\Year5\Internship\STM32H_Example Codes\CURRENT\Dual_Core__High_Level_Arch_STABLE\Dual_Core__High_Level_Arch_STABLE\Dual_Core__High_Level_Arch\Common\Inc\common.h"

#define STATE_INIT							0
#define STATE_IDLE							1
#define STATE_ROBOT_MOVE					2
#define STATE_HUMAN_MOVE					3
#define STATE_CLEAN_UP						4
#define STATE_CHEAT_DETECTED				5
#define STATE_GAME_END						6

#define SUBSTATE_RM_REQ_MOVE				0
#define SUBSTATE_RM_REC_MOVE				1
#define SUBSTATE_RM_MOVE_TO_CM4				2
#define SUBSTATE_RM_WAIT_CM4				3
#define SUBSTATE_RM_CM4_DONE				4

#define SUBSTATE_HM_ACTIVATE				0
#define SUBSTATE_HM_WAIT					1

#define TASK_USER_TURN						0
#define TASK_ROBOT_TURN						1
#define TASK_CLEAN_UP						2
#define TASK_CM4_INIT						3
#define TASK_GAME_END						4

void initTaskGenerator(uint8_t* state, uint8_t* substateRM, uint8_t* substateHM, uint8_t* dataIn);

void taskToDo(uint8_t task);

void HAL_HSEM_FreeCallback(uint32_t SemMask);

#endif /* INC_LEVEL_2_TASK_GENERATOR_H_ */
