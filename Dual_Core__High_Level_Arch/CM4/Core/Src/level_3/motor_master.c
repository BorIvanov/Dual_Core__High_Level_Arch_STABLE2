/*
 * motor_master.c
 *
 *  Created on: Jun 20, 2022
 *      Author: Pascal
 */
#include "level_3/motor_master.h"

void initMotors()
{
	initMotorX();
	initMotorZ();
}

uint8_t move_to_X_and_Z(int16_t posX, int16_t posZ) //MoveToPos
{
	move_to_posX(posX);
	move_to_posZ(posZ);
	return 1;
}

uint8_t HomeMotors(uint8_t homeX, uint8_t homeZ)
{
	if (homeX)
	{
		homeMotorX();
	}
	HAL_Delay(1000);
	if (homeZ)
	{
		homeMotorZ();
	}
	return 1;
}
