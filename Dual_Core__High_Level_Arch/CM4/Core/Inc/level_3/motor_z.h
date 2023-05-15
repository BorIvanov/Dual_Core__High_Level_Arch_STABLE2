/*
 * motorZ.h
 *
 *  Created on: Jun 20, 2022
 *      Author: Pascal
 *
 *  Edited on: 11 May, 2023
 *  	Author: Boris Ivanov
 */

#ifndef INC_MOTOR_Z_H_
#define INC_MOTOR_Z_H_

/* LIBRARIES */
#include "peripheral_devices/gpio.h"
#include "peripheral_devices/tim.h"
#include "motor_master.h"

#include "level_3/motor_z.h"
#include "peripheral_devices/usart.h"
#include "stdio.h"

/* TODO: Defines about specific position needed for game play*/
// Miscellaneous
#define Z_POS_HOME 0 // home position
#define Z_POS_DROP // position where the token can be dropped
#define Z_POS_TOP // position where end-effactor can rotate
#define Z_POS_FLIPPER // rgb/flipper location
#define Z_POS_DUMP_BASE // top of where token roll off after opening the board
#define Z_POS_STORE // Store stack top position
#define Z_CHIP_HEIGHT 7 // Z height of chip in mm
// Stack base when storing tokens
#define Z_POS_STORE_0
#define Z_POS_STORE_1
#define Z_POS_STORE_2
#define Z_POS_STORE_3
#define Z_POS_STORE_4
#define Z_POS_STORE_5
#define Z_POS_STORE_6
// Dump base when cleaning the board
#define Z_POS_DUMP_0
#define Z_POS_DUMP_1
#define Z_POS_DUMP_2
#define Z_POS_DUMP_3
#define Z_POS_DUMP_4
#define Z_POS_DUMP_5




/* FUNCTIONS */
void initMotorZ();
uint8_t homeMotorZ();
uint8_t move_to_posZ(double Zpos);

#endif /* INC_MOTOR_Z_H_ */
