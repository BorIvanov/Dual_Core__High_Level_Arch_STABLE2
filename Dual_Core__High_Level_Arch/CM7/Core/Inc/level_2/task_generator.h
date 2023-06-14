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
#include <stdbool.h>
#include "D:\University\Fontys\Year5\Internship\STM32H_Example Codes\CURRENT\Dual_Core__High_Level_Arch_STABLE\Dual_Core__High_Level_Arch_STABLE\Dual_Core__High_Level_Arch\Common\Inc\common.h"

#define STATE_INIT							0
#define STATE_IDLE							1
#define STATE_ROBOT_TURN					2
#define STATE_USER_TURN						3
#define STATE_CLEAN_UP						4
#define STATE_CHEAT_DETECTED				5
#define STATE_GAME_END						6
#define STATE_START_GAME					7

#define SUBSTATE_RM_REQ_MOVE				0
#define SUBSTATE_RM_REC_MOVE				1
#define SUBSTATE_RM_MOVE_TO_CM4				2
#define SUBSTATE_RM_WAIT_CM4				3
#define SUBSTATE_RM_CM4_DONE				4

#define SUBSTATE_HM_ACTIVATE				0
#define SUBSTATE_HM_WAIT					1

#define ROBOT								0
#define USER								1

#define TASK_USER_TURN						0
#define TASK_ROBOT_TURN						1
#define TASK_CLEAN_UP						2
#define TASK_CM4_INIT						3
#define TASK_GAME_END						4

extern int current_state_CM7;
extern int previous_state_CM7;
extern bool whos_turn; // 0 == ROBOT | 1 == USER
extern bool been_HSEM; // 0 == hasn't passed through HSEM | 1 == has passed



void initTaskGenerator(void);

void taskToDo(uint8_t task);

void HAL_HSEM_FreeCallback(uint32_t SemMask);

void gameplay_loop_CM7(int state);
void exec_state_init(void);
void exec_state_idle(void);
void exec_state_robot_move(void);
void exec_state_user_move(void);
void exec_state_clean_up(void);
void exec_state_cheat_detected(void);
void exec_state_game_end(void);
void exec_state_start_game(void);
int check_state(void);

#endif /* INC_LEVEL_2_TASK_GENERATOR_H_ */
