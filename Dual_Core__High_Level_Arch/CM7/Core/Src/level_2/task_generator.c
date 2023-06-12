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


void initTaskGenerator(uint8_t *state, uint8_t *substateRM, uint8_t *substateHM,
		uint8_t *dataIn)
/* initTaskGenerator: Initializes the states and variables.
 *
 * Activates HSEM notifications to look out for from CM4. Initializes the shared buffer.
 */
{
	subRobotM = substateRM;
	subHumanM = substateHM;
	st = state;
	data = dataIn; // Rx_data

	HAL_HSEM_ActivateNotification(HSEM_CM4_DONE_MASK);
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
	if (task == TASK_ROBOT_TURN)
	{
		memset(SharedBuf, (int) (data[0] - '0'), 1); // writing the Rx_data in shared buff so CM4 can access it
		HSEM_TAKE_RELEASE(HSEM_ROBOT_TURN); 		 // triggers action in CM4
	}
	if (task == TASK_USER_TURN)
	{
		HSEM_TAKE_RELEASE(HSEM_USER_TURN);
	}
	if (task == TASK_CLEAN_UP)
	{
		HSEM_TAKE_RELEASE(HSEM_CLEAN_UP);
	}
}


void HAL_HSEM_FreeCallback(uint32_t SemMask)
/* Function is called automatically when a semaphore is released.
 * This function takes care of HSEM's released from Cortex-M4.
 */
{
	if (SemMask == HSEM_CM4_DONE_MASK) 							// Is CM4 done with it's current task ?
	{
		// chose next state based on current state
		if (*st == STATE_INIT)
		{
			*st = STATE_START;
		}
		if (*st == STATE_ROBOT_MOVE)
		{
			*subRobotM = SUBSTATE_RM_CM4_DONE;
		}
		HAL_HSEM_ActivateNotification(HSEM_CM4_DONE_MASK); 		// reactivate notification
	}
}
