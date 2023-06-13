/*
 * task_manager.c
 *
 *  Created on: Apr 24, 2023
 *      Author: Boris Ivanov
 */
#include "level_2/task_manager.h"

void activate_HSEM_Notifications(void)
/* activate_HSEM_Notifications: Called in the beginning of the
 * program to activate notifications to look out for (ones arriving from CM7) */
{
	HAL_HSEM_ActivateNotification(HSEM_CM7_TO_CM4_MASK);
	HAL_HSEM_ActivateNotification(HSEM_CM4_INIT_MASK);
	HAL_HSEM_ActivateNotification(HSEM_ROBOT_TURN_MASK);
	HAL_HSEM_ActivateNotification(HSEM_USER_TURN_MASK);
	HAL_HSEM_ActivateNotification(HSEM_GAME_END_MASK);
	HAL_HSEM_ActivateNotification(HSEM_CLEAN_UP_MASK);
}

void HAL_HSEM_FreeCallback(uint32_t SemMask)
/* Function is called automatically when a semaphore is released
 * This function takes care of HSEM's released from Cortex-M7 */
{
	// Handle the semaphore release event
	switch (SemMask)
	{
	case HSEM_CM4_INIT_MASK:
		state_flag = STATE_INIT; 			// change state according to command from CM7
		HAL_HSEM_ActivateNotification(HSEM_CM4_INIT_MASK); 	// reactivate notification
		break;

	case HSEM_ROBOT_TURN_MASK:
		state_flag = STATE_ROBOT_TURN; 			// change state according to command from CM7
		HAL_HSEM_ActivateNotification(HSEM_ROBOT_TURN_MASK); // reactivate notification
		break;

	case HSEM_USER_TURN_MASK:
		//humanMove = 0;
		state_flag = STATE_USER_TURN; 			// change state according to command from CM7
		HAL_HSEM_ActivateNotification(HSEM_USER_TURN_MASK); // reactivate notification
		break;

	case HSEM_GAME_END_MASK:
		state_flag = STATE_GAME_END; 			// change state according to command from CM7
		HAL_HSEM_ActivateNotification(HSEM_GAME_END_MASK); // reactivate notification
		break;

	case HSEM_CLEAN_UP_MASK:
		state_flag = STATE_CLEAN_UP; 			// change state according to command from CM7
		HAL_HSEM_ActivateNotification(HSEM_CLEAN_UP_MASK); // reactivate notification
		break;

	default:
		break;
	}
}

void gameplay_loop_CM4(int state)
// gameplay_loop_CM4: The main logic of Cortex-M4
{
	switch (state)
	{
	case STATE_INIT:
		exec_state_init();
		break;

	case STATE_IDLE:
		exec_state_idle();
		break;

	case STATE_ROBOT_TURN:
		exec_state_robot_move();
		break;

	case STATE_USER_TURN:
		exec_state_user_move();
		break;

	case STATE_CLEAN_UP:
		exec_state_clean_up();
		break;

	case STATE_CHEAT_DETECTED:
		exec_state_cheat_detected();
		break;

	case STATE_GAME_END:
		exec_state_game_end();
		break;

	default: // im not sure what needs to happen here yet
		// maybe my default should be idle, maybe not
		break;
	}
}

void exec_state_init(void)
{
	// initialize necessary signals
	// home procedure
	open_all_columns();

	HSEM_TAKE_RELEASE(HSEM_CM4_DONE); // tell CM7 that CM4 is done with task
}

void exec_state_idle(void)
{
	/* Do nothing
	 A perfect place to check for current score and determine if the game ends
	 or check for a cheat move */
}

void exec_state_robot_move(void)
{
	// access "coulmn to be played at" from memory
	// move to that position
	HSEM_TAKE_RELEASE(HSEM_CM4_DONE); // tell CM7 that CM4 is done
}

void exec_state_user_move(void)
{
	// write to mem when user drops a token
	if (1)
	{
		// possibly here include the userDetector (lightgate, PD+IR)
		HSEM_TAKE_RELEASE(HSEM_CM4_DONE);
	}
}

void exec_state_clean_up(void)
{
	open_all_columns();

	HSEM_TAKE_RELEASE(HSEM_CM4_DONE);
}

void exec_state_cheat_detected(void)
{
	// we arrive here from an interrupt from Lightgate (?)
	// Send task that triggers Cheat Detected in CM7
}

void exec_state_game_end(void)
{
	// display appropriate msgs
	HSEM_TAKE_RELEASE(HSEM_CM4_DONE);
}

/* Returns:
		 STATE_INIT							0
		 STATE_IDLE							1
		 STATE_ROBOT_TURN					2
		 STATE_HUMAN_TURN					3
		 STATE_CLEAN_UP						4
		 STATE_CHEAT_DETECTED				5
		 STATE_GAME_END						6
 */
int check_state(void)
{
	return state_flag;
}
