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

uint8_t move_to_X_and_Z(int16_t posX, int16_t posZ)
{
	move_to_posX(posX);
	send_msg((uint8_t*)"\rMotor X has reached final position!\n\r");

	move_to_posZ(posZ);
	send_msg((uint8_t*)"\rMotor Z has reached final position!\n\r");

	return 1;
}

uint8_t HomeMotors(uint8_t homeX, uint8_t homeZ)
{
	if (homeX)
	{
		homeMotorX();
	}
	send_msg((uint8_t*)"\rMotor X has reached final position!\n\r");
	HAL_Delay(1000);
	if (homeZ)
	{
		homeMotorZ();
	}
	send_msg((uint8_t*)"\rMotor Z has reached final position!\n\r");
	return 1;
}
