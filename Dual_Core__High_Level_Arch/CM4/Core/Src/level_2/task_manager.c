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
		current_state_CM4 = STATE_INIT; // change state according to command from CM7
		HAL_HSEM_ActivateNotification(HSEM_CM4_INIT_MASK); // reactivate notification
		break;

	case HSEM_ROBOT_TURN_MASK:
		current_state_CM4 = STATE_ROBOT_TURN; // change state according to command from CM7
		HAL_HSEM_ActivateNotification(HSEM_ROBOT_TURN_MASK); // reactivate notification
		break;

	case HSEM_USER_TURN_MASK:
		//humanMove = 0;
		current_state_CM4 = STATE_USER_TURN; // change state according to command from CM7
		HAL_HSEM_ActivateNotification(HSEM_USER_TURN_MASK); // reactivate notification
		break;

	case HSEM_GAME_END_MASK:
		current_state_CM4 = STATE_GAME_END; // change state according to command from CM7
		HAL_HSEM_ActivateNotification(HSEM_GAME_END_MASK); // reactivate notification
		break;

	case HSEM_CLEAN_UP_MASK:
		current_state_CM4 = STATE_CLEAN_UP; // change state according to command from CM7
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
	send_msg((uint8_t*) "\r🟢🟢🟢 Executing STATE INIT 🟢🟢🟢\n\r");

	// initialize necessary signals
	// home procedure
	open_all_columns();

	HSEM_TAKE_RELEASE(HSEM_CM4_DONE); 	// tell CM7 6that CM4 is done with task
}

void exec_state_idle(void)
{
	send_msg((uint8_t*) "\r⚡⚡⚡ Executing STATE IDLE ⚡⚡⚡\n\r");
	/* Do nothing
	 A perfect place to check for current score and determine if the game ends
	 or check for a cheat move */
}

void exec_state_robot_move(void)
{
	send_msg((uint8_t*) "\r⚡⚡⚡ Executing STATE ROBOT TURN ⚡⚡⚡\n\r");
	// access "column to be played at" from memory
	// move to that position

	send_msg_data((uint8_t*) "\r##### Moving to pos X: %d #####\n\r",
	X_POS_STACK_3);
	send_msg_data((uint8_t*) "\r##### Moving to pos Z: %d #####\n\r",
	Z_POS_STORE_TOP);
	move_to_X_and_Z(X_POS_STACK_3, Z_POS_STORE_TOP); // moves to above storage number 3
	HAL_Delay(1500);
	set_Rotate_Servo(ROTATE_TO_STORE); 				// rotates end-effector down
	HAL_Delay(500);

	move_to_X_and_Z(X_POS_STACK_3, Z_POS_STORE_6); 	// moves down to place token
	HAL_Delay(1500);

	move_to_X_and_Z(X_POS_STACK_3, Z_POS_STORE_TOP); // moves to above storage number 3 (goes back  up safely)
	HAL_Delay(500);

	send_msg_data((uint8_t*) "\r##### Moving to pos X: %d #####\n\r",
	X_POS_COL_1);
	send_msg_data((uint8_t*) "\r##### Moving to pos Z: %d #####\n\r",
	Z_POS_TOP);
	move_to_X_and_Z(X_POS_COL_1, Z_POS_TOP); // Moving above col 1 and going down to drop token
	HAL_Delay(1000);

	HSEM_TAKE_RELEASE(HSEM_CM4_DONE); 	// tell CM7 that CM4 is done
}

void exec_state_user_move(void)
{
	send_msg((uint8_t*) "\r⚡⚡⚡ Executing STATE USER MOVE ⚡⚡⚡\n\r");
	while (1)
	{
		if (checkcoin() != 9 && checkcoin() != -1)
		{
			update_board_mem();
			HSEM_TAKE_RELEASE(HSEM_CM4_DONE); // tell CM7 that CM4 is done with task
			break;
		}
	}
}

void exec_state_clean_up(void)
{
	send_msg((uint8_t*) "\r⚡⚡⚡ Executing STATE CLEAN-UP ⚡⚡⚡\n\r");

	open_all_columns();

	HSEM_TAKE_RELEASE(HSEM_CM4_DONE);	// tell CM7 that CM4 is done with task
}

void exec_state_cheat_detected(void)
{
	send_msg((uint8_t*) "\r⚠⚠⚠ CHEATER DETECTED ⚠⚠⚠\n\r");

	// we arrive here from an interrupt from Lightgate (?)
	// Send task that triggers Cheat Detected in CM7

	HSEM_TAKE_RELEASE(HSEM_CM4_DONE);	// tell CM7 that CM4 is done with task
}

void exec_state_game_end(void)
{
	send_msg((uint8_t*) "\r🛑🛑🛑 Executing STATE CLEAN-UP 🛑🛑🛑\n\r");

	// display appropriate msgs
	HSEM_TAKE_RELEASE(HSEM_CM4_DONE);	// tell CM7 that CM4 is done with task
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
	return current_state_CM4;
}
