/*
 * servo_controller.c
 *
 *  Created on: Apr 24, 2023
 *      Author: Boris Ivanov
 */

#include "level_3/servo_controller.h"

uint32_t t_pulse_rotate = 0;
uint32_t t_pulse_slide = 0;
uint32_t CCR_value_rotate = 0;
uint32_t CCR_value_slide = 0;

void set_Rotate_Servo(float angle)
/* set_Rotate_Servo: Sets the angle of the servo controlling the end-effector rotator
 *
 * @param angle: Angle of rotation in degrees
 * Acceptable values between 1 - 23 degrees
 */
{
	t_pulse_rotate = 10 * ((uint32_t) angle) + CONTROL_PULSE_MIN; 	// from data sheet of Parallax Standard Servo
	CCR_value_rotate = (t_pulse_rotate - CONTROL_PULSE_MIN)
			* (TIMER_COUNTER_PERIOD) / (CONTROL_PULSE_RANGE); 		// mapping the values of us to the range of Timer Counter
	TIM13->CCR1 = CCR_value_rotate; 								// applying value to TIM
}
void set_Slide_Servo(float angle)
/* set_Slide_Servo: Sets the angle of the servo controlling the board opening slider
 *
 * @param angle: Angle of rotation in degrees
 * Acceptable values between 1 - 25 degrees
 */
{
	t_pulse_slide = 10 * ((uint32_t) angle) + CONTROL_PULSE_MIN; 	// from data sheet of Parallax Standard Servo
	CCR_value_slide = (t_pulse_slide - CONTROL_PULSE_MIN)
			* (TIMER_COUNTER_PERIOD) / (CONTROL_PULSE_RANGE); 		// mapping the values of us to the range of Timer Counter
	TIM14->CCR1 = CCR_value_slide; 									// applying value to TIM
}
