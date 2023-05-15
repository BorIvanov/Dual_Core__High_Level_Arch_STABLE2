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

/* TODO: Defines about specific position needed for gameplay*/
// Miscellaneous
#define X_POS_DUMP_BASE
#define X_POS_FLIPPER
#define X_POS_HOME
// Column positions
#define X_POS_COL_1
#define X_POS_COL_2
#define X_POS_COL_3
#define X_POS_COL_4
#define X_POS_COL_5
#define X_POS_COL_6
#define X_POS_COL_7
// left, middle, right store positions
#define X_POS_STACK_1
#define X_POS_STACK_2
#define X_POS_STACK_3



/* FUNCTIONS */
void initMotorX();
uint8_t homeMotorX();
uint8_t moveToPosX(double Xpos);

#endif /* INC_MOTOR_X_H_ */
