/*
 * motorZ.c
 *
 *  Created on: Jun 20, 2022
 *      Author: Pascal
 *
 *  Edited on: 11 May, 2023
 *  	Author: Boris Ivanov
 */
#include "level_3/motor_z.h"

/* TODO: Move to Vars */
uint32_t counterZ;
double position_mm_Z;
int msg_counter_z = 0; 										// Counter limit for messages

uint8_t i_Z = 0;
uint8_t once_Z = 1;

void initMotorZ()
/* Initialises the necessary timers for motor Z */
{
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);   // Start PWM output for motor Z using TIM2 channel 4
    HAL_TIM_Encoder_Start_IT(&htim4, TIM_CHANNEL_ALL);   // Enable encoder interface with interrupt for all channels of TIM4
}

uint8_t homeMotorZ()
/* homeMotorZ: Moves the motor to the home position
 *
 * return: none todo: make a return for error catching and/or others
 * */
{
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 115); 	// set PWM of motor

	set_Direction_Z(); 									// counter-clockwise | towards HOME TODO:Change name
	set_Ready_Z(); 										// enable motor TODO:Change name


	while (!get_Homing_Z()) 							// wait until home-switch is hit
	{

	}
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 0); 	// set PWM of motor
	reset_Ready_Z(); 									//disable motor
	HAL_Delay(1000);
	/* reset variables */
	position_mm_Z = 0.0;
	counterZ = 0;
	i_Z = 0;
	__HAL_TIM_SET_COUNTER(&htim4, 0); 					// reset timer
	return 1;
}

uint8_t move_to_posZ(double posZ)
/* move_to_posZ: Moves the motor to a position Z cm away from the home position
 *
 * @param posZ: Centimetres away from the home position
 *  RANGE posZ:  1 - 53 cm
 */
{
	counterZ = __HAL_TIM_GET_COUNTER(&htim4);					// get timer value
	position_mm_Z = (double) ((counterZ / 3855) + (i_Z * 17));	// get position
	double delta = posZ - position_mm_Z;						// calculate delta

	set_Ready_Z(); 												// enable motor
	while (abs(delta) > 1.5)										// desired accuracy in cm? TODO:prove it
	{
		if (delta > 0)
		{
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 450);	// adjust speed (prev val 340)
			reset_Direction_Z(); 								// clockwise | towards END/up
		}
		else if (delta < 0)
		{
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 100); 	// adjust speed (prev val 120)
			set_Direction_Z(); 									// counter-clockwise | towards HOME/down
		}
		else
			break;

		counterZ = __HAL_TIM_GET_COUNTER(&htim4);				// update counter
		/* Some Magic */
		if (counterZ > 61680 && delta > 0 && once_Z){
			once_Z = 0;}
		else if (counterZ < 3855 && delta > 0 && !once_Z){
			once_Z = 1, i_Z += 1;}
		else if (counterZ < 3855 && delta < 0){
			once_Z = 0;}
		else if (counterZ > 61680 && delta < 0 && !once_Z){
			once_Z = 1, i_Z -= 1;}
		/* End of Magic */

		position_mm_Z = (double) ((counterZ / 3855) + (i_Z * 17));  // update position
		delta = posZ - position_mm_Z;								// update delta

		// limit msg sending every Nth itteration
		if (msg_counter_z % 200000 == 0)							// TODO: move 200000 to a define freq of msging
		{
			send_msg_data((uint8_t*)"\rCurrently @ Pos Z: %d\n\r", (int)position_mm_Z);
		}
		msg_counter_z++;

	}
	reset_Direction_Z(); 					// reverses the direction to stop it from dropping due gravity
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 200); //  PWM to lower value to improve power consumption
	return 1;
}

