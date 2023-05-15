/*
 * init_CM4.c
 *
 *  Created on: Apr 24, 2023
 *      Author: Boris Ivanov
 */

/* Includes ------------------------------------------------------------------*/

#include "level_2/init_CM4.h"


void start_PWM(void)
/* start_PWM: Function which initialises the PWM TIMERs 2,13,14. */
{
	HAL_TIM_PWM_Start(&htim13, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
}

void init_Movement(void)
/* start_Movement: Function which initialises the motors and servos */
{
	initMotors();
	set_Enable_Power();
	start_PWM();
}

void init_MX_init(void)
/* start_MX_init: Function which initialises the STM32H peripherals */
{
	MX_ADC1_Init();
	MX_TIM2_Init();
	MX_TIM3_Init();
	MX_TIM4_Init();
	MX_TIM13_Init();
	MX_TIM14_Init();
}

void init_Start_Up(void)
/* init_Start_Up: Function to initialise the whole system and set inital values to PWMs
 *	The microcontroller peripherals. The Motors and Servos.
 *
 *	Homes the servos. TODO: Home the motors
 */
{
	init_MX_init();
	init_Movement();

	HomeMotors(1, 1);

	set_Slide_Servo(SLIDE_CLOSED); 		// part of homing procedure
	set_Rotate_Servo(ROTATE_NEUTRAL); 	// part of homing procedure
}



