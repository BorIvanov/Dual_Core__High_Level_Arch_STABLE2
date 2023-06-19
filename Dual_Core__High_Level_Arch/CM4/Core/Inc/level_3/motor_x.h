/*
 * motor_X.h
 *
 *  Created on: Jun 20, 2022
 *      Author: Pascal
 *
 *  Edited on: 11 May, 2023
 *  	Author: Boris Ivanov
 */

#ifndef INC_MOTOR_X_H_
#define INC_MOTOR_X_H_

/* LIBRARIES */
#include "peripheral_devices/gpio.h"
#include "peripheral_devices/tim.h"
#include "motor_master.h"

#include "level_3/motor_x.h"
#include "peripheral_devices/usart.h"
#include <stdio.h>

// Miscellaneous
#define X_END_LIMIT 47 			// the last few mm are tricky, due to physical cable block (black holder)
#define X_POS_DUMP_BASE 48 		// however the robot can only move to 47. Then it gets stuck
#define X_POS_FLIPPER 24.5		// position of flipper
#define X_POS_HOME 0			// home position

// Column positions
#define X_POS_COL_1 1.5			// column 1 position
#define X_POS_COL_2 8.4			// column 2 position
#define X_POS_COL_3 13.5		// column 3 position
#define X_POS_COL_4 18.0		// column 4 position
#define X_POS_COL_5 23.1		// column 5 position
#define X_POS_COL_6 27.6		// column 6 position
#define X_POS_COL_7 32.9		// column 7 position


// left, middle, right store positions
#define X_POS_STACK_1 1.5		// position for store location 1
#define X_POS_STACK_2 7.5		// position for store location 2
#define X_POS_STACK_3 12.5		// position for store location 3


/* FUNCTIONS */
void initMotorX();
uint8_t homeMotorX();
uint8_t move_to_posX(double posX);

#endif /* INC_MOTOR_X_H_ */
