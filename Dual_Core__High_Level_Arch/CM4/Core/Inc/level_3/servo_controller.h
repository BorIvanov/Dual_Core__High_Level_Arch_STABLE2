/*
 * servo_controller.h
 *
 *  Created on: Apr 24, 2023
 *      Author: Boris Ivanov
 *
 *  Description: Controls the servo for the board opener and for the head rotation.
 */

#ifndef INC_LEVEL_3_SERVO_CONTROLLER_H_
#define INC_LEVEL_3_SERVO_CONTROLLER_H_

/* LIBRARIES */
#include "main.h"
#include "string.h"

/* DEFINES */
#define CONTROL_PULSE_MAX 2420 		// Parallax data sheet
#define CONTROL_PULSE_MIN 620 		// Parallax data sheet
#define CONTROL_PULSE_RANGE CONTROL_PULSE_MAX-CONTROL_PULSE_MIN
#define TIMER_COUNTER_PERIOD 60000 	// TIM13/14 AAR

#define SLIDE_CLOSED 1.0	// Doesn't turn lower than 1 degree
#define SLIDE_OPEN 25.0		// Doesn't turn higher than 25 degrees

/* This is the natural order of opening the columns
 * on the slider piece. The mechanical construction
 * forces it. When clearing the board col by col, refer to this:
 * Column 2 opens first, then 6, 7, 4, 1, 5 and column 3 is opened last.
 * The same order is kept bellow.
 */
#define OPEN_COL_2 6.0  	// 3.30% Duty Cycle
#define OPEN_COL_6 7.0  	// 3.88% Duty Cycle
#define OPEN_COL_7 8.0 		// 4.40% Duty Cycle
#define OPEN_COL_4 10.0 	// 5.50% Duty Cycle
#define OPEN_COL_1 15.0 	// 8.30% Duty Cycle
#define OPEN_COL_5 16.0 	// 8.90% Duty Cycle
#define OPEN_COL_3 23.0 	// 12.7% Duty Cycle

#define ROTATE_NEUTRAL 5.30 	// 2.80% Duty Cycle | This position points to the operator
#define ROTATE_TO_STACK 13.0	// 7.20% Duty Cycle
#define ROTATE_TO_DROP 23.0 	// 12.8% Duty Cycle

/* FUNCTIONS */
void set_Rotate_Servo(float angle);
void set_Slide_Servo(float angle);

#endif /* INC_LEVEL_3_SERVO_CONTROLLER_H_ */
