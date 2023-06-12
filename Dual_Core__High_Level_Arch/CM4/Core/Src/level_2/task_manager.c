/*
 * task_manager.c
 *
 *  Created on: Apr 24, 2023
 *      Author: Boris Ivanov
 */
#include "level_2/task_manager.h"

void activate_HSEM_Notifications()
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
		state = STATE_INIT;
		HAL_HSEM_ActivateNotification(HSEM_CM4_INIT_MASK);
		break;

	case HSEM_ROBOT_TURN_MASK:
		//memcpy(data, SharedBuf, 1);			// get column data from share buffer
		//state = STATE_ROBOT_MOVE; 			// Changes the state in this core
		HAL_HSEM_ActivateNotification(HSEM_ROBOT_TURN_MASK); // reactivate notification
		break;

	case HSEM_USER_TURN_MASK:
		//humanMove = 0;
		state = STATE_HUMAN_MOVE;			// Changes the state in this core
		HAL_HSEM_ActivateNotification(HSEM_USER_TURN_MASK); // reactivate notification
		break;

	case HSEM_GAME_END_MASK:
		break;

	case HSEM_CLEAN_UP_MASK:
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
		state_init();
		break;

	case STATE_IDLE: // starting state
		state_idle();
		break;

	case STATE_ROBOT_MOVE:
		state_robot_move();
		break;

	case STATE_HUMAN_MOVE:
		state_human_move();
		break;

	case STATE_CLEAN_UP:
		state_clean_up();
		break;

	case STATE_CHEAT_DETECTED:
		state_cheat_detected();
		break;

	case STATE_GAME_END:
		state_game_end();
		break;

	default: // im not sure what needs to happen here yet
		// maybe my default should be idle, maybe not
		break;
	}
}

void state_init()
{
	// initialize necessary signals
	// home procedure
	open_all_columns();

	HSEM_TAKE_RELEASE(HSEM_CM4_DONE); // tell CM7 that CM4 is done with task
}

void state_idle()
{
	/* Do nothing
	 A perfect place to check for current score and determine if the game ends
	 or check for a cheat move */
}

void state_robot_move()
{
	// access "coulmn to be played at" from memory
	// move to that position
	state = STATE_IDLE;
	HSEM_TAKE_RELEASE(HSEM_CM4_DONE); // tell CM7 that CM4 is done
}

void state_human_move()
{
	// write to mem when user drops a token
	if (1)
	{
		// possibly here include the userDetector (lightgate, PD+IR)
		state = STATE_IDLE;
		HSEM_TAKE_RELEASE(HSEM_CM4_DONE);
	}
}

void state_clean_up()
{
	open_all_columns();

	state = STATE_IDLE;
	HSEM_TAKE_RELEASE(HSEM_CM4_DONE);
}

void state_cheat_detected()
{
	// we arrive here from an interrupt from Lightgate (?)
	// Send task that triggers Cheat Detected in CM7
}

void state_game_end()
{
	// display appropriate msgs
	HSEM_TAKE_RELEASE(HSEM_CM4_DONE);
}
