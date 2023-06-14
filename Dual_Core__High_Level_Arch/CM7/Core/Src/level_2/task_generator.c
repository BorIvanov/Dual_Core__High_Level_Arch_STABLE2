/*
 * @file:  task_generator.c
 * @brief: Initialising the Task Generator and setting up tasks.
 *
 *  Created on: 20 mei 2022
 *      Author: Pascal
 *
 *  Edited on: 12/04/2023
 *  	Author: Boris Ivanov
 *
 * This is achieved by HSEM. By taking and releasing a specific HSEM on CM7,
 * and if a notification for this HSEM is activate on CM4, the CM4 will trigger
 * HSEM_FreeCallback on CM4. Which in turn will handle the semaphore release event.
 *
 ******************************************************************************
 */

#include "level_2/task_generator.h"

uint8_t *subRobotM;
uint8_t *subHumanM;
uint8_t *st;
uint8_t *data;
int current_state_CM7 = STATE_INIT;
int previous_state_CM7 = -1;
bool whos_turn = USER;
bool been_HSEM = 0;


void initTaskGenerator()
/* initTaskGenerator: Initializes the states and variables.
 *
 * Activates HSEM notifications to look out for from CM4. Initializes the shared buffer.
 */
{


	HAL_HSEM_ActivateNotification(HSEM_CM4_DONE_MASK);
	HAL_HSEM_ActivateNotification(HSEM_CHEAT_MASK);
	memset(SharedBuf, 0, 10); // init shared buffer
}

void taskToDo(uint8_t task)
/* taskToDo: Sends the tasks to CM4 through the means of HSEM.
 *
 * When an HSEM is released, changes occur in other core. Usually
 * this is a state change, or information copied/set to memory, local variables
 *
 * task: task to be sent to CM4
 */
{
	switch (task)
	{
	case TASK_CM4_INIT:
		HSEM_TAKE_RELEASE(HSEM_CM4_INIT);
		break;

	case TASK_ROBOT_TURN:
		HSEM_TAKE_RELEASE(HSEM_ROBOT_TURN);
		break;

	case TASK_USER_TURN:
		HSEM_TAKE_RELEASE(HSEM_USER_TURN);
		break;

	case TASK_GAME_END:
		HSEM_TAKE_RELEASE(HSEM_GAME_END);
		break;

	case TASK_CLEAN_UP:
		HSEM_TAKE_RELEASE(HSEM_CLEAN_UP);
		break;

	default:
		break;
	}
}

void HAL_HSEM_FreeCallback(uint32_t SemMask)
/* Function is called automatically when a semaphore is released.
 * This function takes care of HSEM's released from Cortex-M4.
 *
 * This progresses the FSM of Cortex-M7,
 * whenever a HSEM is released from CM4
 */
{
	been_HSEM = 1;
	if (SemMask == HSEM_CM4_DONE_MASK) 	// Is CM4 done with it's current task ?
	{
		// chose next state based on current state
		if (current_state_CM7 == STATE_INIT)
		{
			current_state_CM7 = STATE_START_GAME;
		}
		if (current_state_CM7 == STATE_ROBOT_TURN)
		{
			current_state_CM7 = STATE_IDLE;
		}
		if (current_state_CM7 == STATE_USER_TURN)
		{
			current_state_CM7 = STATE_IDLE;
		}
		HAL_HSEM_ActivateNotification(HSEM_CM4_DONE_MASK); // reactivate notification
	}
}

void gameplay_loop_CM7(int state)
// gameplay_loop_CM7: The main logic of Cortex-M4
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

	case STATE_START_GAME:
		exec_state_start_game();
		break;

	default: // im not sure what needs to happen here yet
		// maybe my default should be idle, maybe not
		break;
	}
}

void exec_state_init(void)
{
	HSEM_TAKE_RELEASE(HSEM_CM4_INIT); // tell CM4 to initialise
}

void exec_state_idle(void)
{
	if (whos_turn == USER)
	{
		whos_turn = !whos_turn; // robot's turn
		current_state_CM7 = STATE_ROBOT_TURN; // go to robot move state
	}
	else // robot's turn
	{
		whos_turn = !whos_turn;	// user's turn
		current_state_CM7 = STATE_USER_TURN; // go to user move state
	}
}

void exec_state_robot_move(void)
{
	HSEM_TAKE_RELEASE(HSEM_ROBOT_TURN); // tell CM4 to execute robot move
}

void exec_state_user_move(void)
{
	HSEM_TAKE_RELEASE(HSEM_USER_TURN);// tell CM4 that it can validate user inputs
}

void exec_state_clean_up(void)
{
	HSEM_TAKE_RELEASE(HSEM_CLEAN_UP);	// tell CM4 to prepare for next game
}

void exec_state_cheat_detected(void)
{

}

void exec_state_game_end(void)
{
	HSEM_TAKE_RELEASE(HSEM_GAME_END);// tell CM4 to display user msgs for game end
}

void exec_state_start_game(void)
{
	// TODO: prepare vars.c and others ?

	current_state_CM7 = STATE_USER_TURN; // go to next state
	whos_turn = USER;
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
	return current_state_CM7;
}
