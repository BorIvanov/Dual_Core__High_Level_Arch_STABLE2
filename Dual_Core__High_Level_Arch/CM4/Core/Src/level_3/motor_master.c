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
	send_msg((uint8_t*)"\r**** Motor X is at the final position! ****\n\r");

	move_to_posZ(posZ);
	send_msg((uint8_t*)"\r**** Motor Z is at the final position! ****\n\r");

	return 1;
}

uint8_t HomeMotors(uint8_t homeX, uint8_t homeZ)
{
	send_msg((uint8_t*)"\r#### HOMING Motor X №###\n\r");
	if (homeX)
	{
		homeMotorX();
	}
	send_msg((uint8_t*)"\r######## Motor X is at HOME ########\n\r");

	HAL_Delay(250);
	send_msg((uint8_t*)"\r#### HOMING Motor Z ####\n\r");
	if (homeZ)
	{
		homeMotorZ();
	}
	send_msg((uint8_t*)"\r######## Motor Z is at HOME ########\n\r");
	return 1;
}
// Fully working set up to get the arms to the top
// and simulate dropping down a token in each column
/*
 	 	set_Rotate_Servo(ROTATE_NEUTRAL);
		homeMotorX();
		move_to_X_and_Z(0, Z_POS_TOP);
		set_Rotate_Servo(ROTATE_TO_DROP);

		// Moving above col 1 and going down to drop token
		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_COL_1);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_TOP);
		move_to_X_and_Z(X_POS_COL_1, Z_POS_TOP);
		HAL_Delay(1000);
		move_to_X_and_Z(X_POS_COL_1, Z_POS_DROP);
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_1, Z_POS_TOP);

		// Moving above col 2 and going down to drop token
		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_COL_2);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_TOP);
		move_to_X_and_Z(X_POS_COL_2, Z_POS_TOP);
		HAL_Delay(1000);
		move_to_X_and_Z(X_POS_COL_2, Z_POS_DROP);
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_2, Z_POS_TOP);

		// Moving above col 3 and going down to drop token
		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_COL_3);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_TOP);
		move_to_X_and_Z(X_POS_COL_3, Z_POS_TOP);
		HAL_Delay(1000);
		move_to_X_and_Z(X_POS_COL_3, Z_POS_DROP);
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_3, Z_POS_TOP);

		// Moving above col 4 and going down to drop token
		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_COL_4);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_TOP);
		move_to_X_and_Z(X_POS_COL_4, Z_POS_TOP);
		HAL_Delay(1000);
		move_to_X_and_Z(X_POS_COL_4, Z_POS_DROP);
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_4, Z_POS_TOP);

		// Moving above col 5 and going down to drop token
		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_COL_5);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_TOP);
		move_to_X_and_Z(X_POS_COL_5, Z_POS_TOP);
		HAL_Delay(1000);
		move_to_X_and_Z(X_POS_COL_5, Z_POS_DROP);
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_5, Z_POS_TOP);

		// Moving above col 6 and going down to drop token
		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_COL_6);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_TOP);
		move_to_X_and_Z(X_POS_COL_6, Z_POS_TOP);
		HAL_Delay(1000);
		move_to_X_and_Z(X_POS_COL_6, Z_POS_DROP);
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_6, Z_POS_TOP);

		// Moving above col 7 and going down to drop token
		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_COL_7);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_TOP);
		move_to_X_and_Z(X_POS_COL_7, Z_POS_TOP);
		HAL_Delay(1000);
		move_to_X_and_Z(X_POS_COL_7, Z_POS_DROP);
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_7, Z_POS_TOP);

 */

// Fully worked out "go to dump base" and lower to pick up tokens
/*		set_Rotate_Servo(ROTATE_NEUTRAL);

		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_DUMP_BASE);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_DUMP_BASE);
		move_to_X_and_Z(X_POS_DUMP_BASE, Z_POS_DUMP_BASE);
		HAL_Delay(1500);

		set_Rotate_Servo(ROTATE_TO_STACK);
		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_DUMP_BASE);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_DUMP_5);
		move_to_X_and_Z(X_POS_DUMP_BASE, Z_POS_DUMP_5);
		HAL_Delay(1500);

		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_DUMP_BASE);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_DUMP_4);
		move_to_X_and_Z(X_POS_DUMP_BASE, Z_POS_DUMP_4);
		HAL_Delay(1500);

		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_DUMP_BASE);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_DUMP_3);
		move_to_X_and_Z(X_POS_DUMP_BASE, Z_POS_DUMP_3);
		HAL_Delay(1500);

		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_DUMP_BASE);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_DUMP_2);
		move_to_X_and_Z(X_POS_DUMP_BASE, Z_POS_DUMP_2);
		HAL_Delay(1500);

		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_DUMP_BASE);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_DUMP_1);
		move_to_X_and_Z(X_POS_DUMP_BASE, Z_POS_DUMP_1);
		HAL_Delay(1500);

		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_DUMP_BASE);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_DUMP_0);
		move_to_X_and_Z(X_POS_DUMP_BASE, Z_POS_DUMP_0);
		HAL_Delay(1500);


		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_DUMP_BASE);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_DUMP_BASE);
		move_to_X_and_Z(X_POS_DUMP_BASE, Z_POS_DUMP_BASE);
 */

// Fully worked out "go above flipper" and lower the token
/*
		set_Rotate_Servo(ROTATE_NEUTRAL);

		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_FLIPPER);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_FLIPPER_BASE);
		move_to_X_and_Z(X_POS_FLIPPER, Z_POS_FLIPPER_BASE);
		HAL_Delay(1500);
		set_Rotate_Servo(ROTATE_TO_STACK);
		HAL_Delay(500);

		move_to_X_and_Z(X_POS_FLIPPER, Z_POS_FLIPPER);
		HAL_Delay(1500);

		move_to_X_and_Z(X_POS_FLIPPER, Z_POS_FLIPPER_BASE);
		HAL_Delay(500);
 */

// Fully worked out "go to store location" and lower into each one
/*
		set_Rotate_Servo(ROTATE_NEUTRAL);

		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_FLIPPER);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_FLIPPER_BASE);
		move_to_X_and_Z(X_POS_STACK_1, Z_POS_STORE_TOP);
		HAL_Delay(1500);
		set_Rotate_Servo(ROTATE_TO_STORE);
		HAL_Delay(500);

		move_to_X_and_Z(X_POS_STACK_1, Z_POS_STORE_6);
		HAL_Delay(1500);

		move_to_X_and_Z(X_POS_STACK_1, Z_POS_STORE_TOP);
		HAL_Delay(500);

		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_FLIPPER);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_FLIPPER_BASE);
		move_to_X_and_Z(X_POS_STACK_2, Z_POS_STORE_TOP);
		HAL_Delay(1500);
		set_Rotate_Servo(ROTATE_TO_STORE);
		HAL_Delay(500);

		move_to_X_and_Z(X_POS_STACK_2, Z_POS_STORE_6);
		HAL_Delay(1500);

		move_to_X_and_Z(X_POS_STACK_2, Z_POS_STORE_TOP);
		HAL_Delay(500);

		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_FLIPPER);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_FLIPPER_BASE);
		move_to_X_and_Z(X_POS_STACK_3, Z_POS_STORE_TOP);
		HAL_Delay(1500);
		set_Rotate_Servo(ROTATE_TO_STORE);
		HAL_Delay(500);

		move_to_X_and_Z(X_POS_STACK_3, Z_POS_STORE_6);
		HAL_Delay(1500);

		move_to_X_and_Z(X_POS_STACK_3, Z_POS_STORE_TOP);
		HAL_Delay(500);
 */
