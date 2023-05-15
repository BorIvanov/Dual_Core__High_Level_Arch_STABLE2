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

/* TODO: Move to Variables.c */
uint32_t counterZ;
double position_mm_Z;

uint8_t i_Z = 0;
uint8_t once_Z = 1;

void initMotorZ()
/* Initialises the necessary timers for motor Z */
{
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
	HAL_TIM_Encoder_Start_IT(&htim4, TIM_CHANNEL_ALL);
}

uint8_t homeMotorZ()
/* homeMotorZ: Moves the motor to the home position */
{
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 160); // set speed of motor

	set_Direction_Z(); // counter-clockwise | towards HOME
	set_Ready_Z(); // enable motor


	while (!get_Homing_Z()) 			// wait until home-switch is hit
	{

	}
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 200); // set speed of motor
	reset_Ready_Z(); //disable motor
	//HAL_GPIO_WritePin(Ready_Z_GPIO_Port, Ready_Z_Pin, GPIO_PIN_RESET);
	HAL_Delay(1000);
	/* Initialise variables */
	position_mm_Z = 0.0;
	counterZ = 0;
	i_Z = 0;
	__HAL_TIM_SET_COUNTER(&htim4, 0); // reset timer
	moveToPosZ(15); // move away from home position
	return 1;
}

uint8_t moveToPosZ(double Zpos)
/* moveToPosZ: Moves the motor to a position Z cm away from the home position
 *
 * @param Zpos: Centimetres away from the home position
 *  RANGE Zpos:  1 - 53 cm
 */
{
	counterZ = __HAL_TIM_GET_COUNTER(&htim4);
	position_mm_Z = (double) ((counterZ / 3855) + (i_Z * 17));
	double delta = Zpos - position_mm_Z;

	set_Ready_Z(); // enable motor
	while (abs(delta) > 2)
	{
		if (delta > 0)
		{
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 340); // adjust speed (val 340)
			reset_Direction_Z(); // clockwise | towards END
		}
		else if (delta < 0)
		{
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 100); // adjust speed (val 120)
			set_Direction_Z(); // counter-clockwise | towards HOME
		}
		else
		{
			break;
		}
		counterZ = __HAL_TIM_GET_COUNTER(&htim4);
		if (counterZ > 61680 && delta > 0 && once_Z)
		{
			once_Z = 0;
		}
		else if (counterZ < 3855 && delta > 0 && !once_Z)
		{
			once_Z = 1;
			i_Z += 1;
		}
		else if (counterZ < 3855 && delta < 0)
		{
			once_Z = 0;
		}
		else if (counterZ > 61680 && delta < 0 && !once_Z)
		{
			once_Z = 1;
			i_Z -= 1;
		}
		position_mm_Z = (double) ((counterZ / 3855) + (i_Z * 17));
		delta = Zpos - position_mm_Z;
		uint8_t send[30];
		sprintf(send, "%f \r\n %u \r\n", position_mm_Z, i_Z);
		ST_LINK_WRITE(send, sizeof(send));
		HAL_Delay(50);

		//		if(abs(delta) < 60){
		//			y = 2*(pow(abs(delta), 0.49)) + 215;
		//			if(y>250){
		//				y = 250;
		//			}
		//		} else {
		//			y = 250;
		//		}
		//
		//		i++;
		//		if(i == 200){
		//			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, y);
		//			i = 0;
		//		}
	}
	reset_Direction_Z();
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 200);
	return 1;
}

