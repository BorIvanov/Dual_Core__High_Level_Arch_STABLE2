/*
 * task_manager.h
 *
 *  Created on: Apr 24, 2023
 *      Author: Boris Ivanov
 *
 *  Description: Receives tasks generated by C-M7. Based on the task given, the states of C-M4 will change accordingly,
 *  together with any necessary data changes.
 *
 */

#ifndef INC_LEVEL_2_TASK_MANAGER_H_
#define INC_LEVEL_2_TASK_MANAGER_H_

#include "main.h"
#include <string.h>
#include "level_2/board_opener.h"
#include "D:\University\Fontys\Year5\Internship\STM32H_Example Codes\CURRENT\Dual_Core__High_Level_Arch_STABLE\Dual_Core__High_Level_Arch_STABLE\Dual_Core__High_Level_Arch\Common\Inc\common.h"

/* DEFINES */ //TODO: redefine
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

/* VARIABLES */

/* FUNCTIONS */
void activate_HSEM_Notifications(void);
void gameplay_loop_CM4(int state);
void state_init();
void state_idle();
void state_robot_move();
void state_human_move();
void state_clean_up();
void state_cheat_detected();
void state_game_end();

#endif /* INC_LEVEL_2_TASK_MANAGER_H_ */
