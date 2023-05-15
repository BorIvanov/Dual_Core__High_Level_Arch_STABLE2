/*
 * motorX.c
 *
 *  Created on: Jun 20, 2022
 *      Author: Pascal
 *
 *  Edited on: 11 May, 2023
 *  	Author: Boris Ivanov
 */
#include "level_3/motor_x.h"

/* TODO: Move to Variables.c */
uint32_t counterX;
double position_mm_X;

uint8_t i_X = 0;
uint8_t once_X = 1;

void initMotorX()
/* Initialises the necessary timers for motor X */
{
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	HAL_TIM_Encoder_Start_IT(&htim3, TIM_CHANNEL_ALL);
}

uint8_t homeMotorX()
/* homeMotorX: Moves the motor to the home position */
{

	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 140); // set PWM of motor

	set_Direction_X(); // counter-clockwise  | towards HOME
	set_Ready_X(); // enables motor X

	while (!get_Homing_X())
	{

	}
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 0); // set PWM of motor
	reset_Ready_X(); // disables motor
	//HAL_GPIO_WritePin(Ready_X_GPIO_Port, Ready_X_Pin, GPIO_PIN_RESET);
	HAL_Delay(1000);
	/* Initialise variables */
	position_mm_X = 0.0;
	counterX = 0;
	i_X = 0;
	__HAL_TIM_SET_COUNTER(&htim3, 0); // reset timer
	moveToPosX(10); // move away from home position
	return 1;
}

uint8_t moveToPosX(double Xpos)
/* moveToPosX: Moves the motor to a position X cm away from the home position
 *
 * @param Zpos: Centimetres away from the home position
 *  RANGE Zpos:  TODO: Determine it
 */
{
	counterX = __HAL_TIM_GET_COUNTER(&htim3);
	position_mm_X = (double) ((counterX / 3855) + (i_X * 17));
	double delta = Xpos - position_mm_X;

	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 120); // slower speed chosen deliberatly (val 140)
	set_Ready_X(); // enable motor
	while (abs(delta) > 2)
	{
		if (delta > 0)
		{
			reset_Direction_X(); // clockwise | towards END
		}
		else if (delta < 0)
		{
			set_Direction_X();  // counter-clockwise | towards HOME
		}
		else
		{
			break;
		}
		counterX = __HAL_TIM_GET_COUNTER(&htim3);
		if (counterX > 61680 && delta > 0 && once_X)
		{
			once_X = 0;
		}
		else if (counterX < 3855 && delta > 0 && !once_X)
		{
			once_X = 1;
			i_X += 1;
		}
		else if (counterX < 3855 && delta < 0)
		{
			once_X = 0;
		}
		else if (counterX > 61680 && delta < 0 && !once_X)
		{
			once_X = 1;
			i_X -= 1;
		}
		position_mm_X = (double) ((counterX / 3855) + (i_X * 17));
		delta = Xpos - position_mm_X;
		//		uint8_t send[30];
		//		sprintf(send, "%ld \r\n %d \r\n", position_mm_X, i_X);
		//		ST_LINK_WRITE(send, sizeof(send));
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
		//			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, y);
		//			i = 0;
		//		}
	}
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 0);
	HAL_GPIO_WritePin(Ready_X_GPIO_Port, Ready_X_Pin, GPIO_PIN_RESET);
	return 1;
}

