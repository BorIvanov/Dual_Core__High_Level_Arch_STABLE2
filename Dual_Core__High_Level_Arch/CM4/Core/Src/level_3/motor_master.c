/*
 * motor_master.c
 *
 *  Created on: Jun 20, 2022
 *      Author: Pascal
 */
#include "level_3/motor_master.h"

void initMotors()
/* Initialising timers for motors */
{
	initMotorX();
	initMotorZ();
}

uint8_t move_to_X_and_Z(int16_t posX, int16_t posZ)
/* move_to_X_and_Z: moves both motor, X axis --> Z-axis
 *
 * param1 posX: position of the X axis locations defined in motor_x.h
 * param2 posZ: position of the Z axis locations defined in motor_z.h
 *
 * return none: TODO: a return could be implemented for various feedback
 */
{
	move_to_posX(posX);
	send_msg((uint8_t*) "\r**** Motor X is at the final position! ****\n\r");

	move_to_posZ(posZ);
	send_msg((uint8_t*) "\r**** Motor Z is at the final position! ****\n\r");

	return 1;
}

uint8_t HomeMotors(uint8_t homeX, uint8_t homeZ)
/* HomeMotors: homes either motor, or both
 *
 * param1 homeX: 1 homed, 0 skip
 * param2 homeZ: 1 homed, 0 skip
 *
 * return none: TODO: a return could be implemented for various feedback
 */
{
	send_msg((uint8_t*) "\r#### HOMING Motor X №###\n\r");
	if (homeX)
	{
		homeMotorX();
	}
	send_msg((uint8_t*) "\r######## Motor X is at HOME ########\n\r");

	HAL_Delay(250);
	send_msg((uint8_t*) "\r#### HOMING Motor Z ####\n\r");
	if (homeZ)
	{
		homeMotorZ();
	}
	send_msg((uint8_t*) "\r######## Motor Z is at HOME ########\n\r");
	return 1;
}
/*
 * To see how the code bellow function
 * simply paste it into the main.c file of CM4
 * and run it.
 *
 * TODO: All sequences could be moved to function/s
 * TODO: Uncomment sections bellow to visually see better
 */

// Fully working set up to get the arm to the top
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
 move_to_X_and_Z(X_POS_DUMP_BASE, Z_POS_DUMP_BASE); // move above the dump base
 HAL_Delay(1500);

 set_Rotate_Servo(ROTATE_TO_STACK);
 send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_DUMP_BASE);
 send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_DUMP_5);
 move_to_X_and_Z(X_POS_DUMP_BASE, Z_POS_DUMP_5); // move down to pick token from top pos
 HAL_Delay(1500);

 send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_DUMP_BASE);
 send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_DUMP_4);
 move_to_X_and_Z(X_POS_DUMP_BASE, Z_POS_DUMP_4); // move down to pick token from top pos - 1
 HAL_Delay(1500);

 send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_DUMP_BASE);
 send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_DUMP_3);
 move_to_X_and_Z(X_POS_DUMP_BASE, Z_POS_DUMP_3); // move down to pick token from top pos - 2
 HAL_Delay(1500);

 send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_DUMP_BASE);
 send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_DUMP_2);
 move_to_X_and_Z(X_POS_DUMP_BASE, Z_POS_DUMP_2); // move down to pick token from top pos -3
 HAL_Delay(1500);

 send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_DUMP_BASE);
 send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_DUMP_1);
 move_to_X_and_Z(X_POS_DUMP_BASE, Z_POS_DUMP_1); // move down to pick token from top pos - 4
 HAL_Delay(1500);

 send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_DUMP_BASE);
 send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_DUMP_0);
 move_to_X_and_Z(X_POS_DUMP_BASE, Z_POS_DUMP_0); // move to the very bottom of the dump location
 HAL_Delay(1500);


 send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_DUMP_BASE);
 send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_DUMP_BASE);
 move_to_X_and_Z(X_POS_DUMP_BASE, Z_POS_DUMP_BASE); // move above the dump base (go back out)
 */

// Fully worked out "go above flipper/rgb" and lower the token
/*
 set_Rotate_Servo(ROTATE_NEUTRAL);

 send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_FLIPPER);
 send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_FLIPPER_BASE);
 move_to_X_and_Z(X_POS_FLIPPER, Z_POS_FLIPPER_BASE); // move above sensor location
 HAL_Delay(1500);
 set_Rotate_Servo(ROTATE_TO_STACK);
 HAL_Delay(500);

 move_to_X_and_Z(X_POS_FLIPPER, Z_POS_FLIPPER); // lower down to sensor
 HAL_Delay(1500);

 move_to_X_and_Z(X_POS_FLIPPER, Z_POS_FLIPPER_BASE); // move above sensor (go up)
 HAL_Delay(500);
 */

// Fully worked out "go to store location" and lower into each one
/*
 set_Rotate_Servo(ROTATE_NEUTRAL);

 send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_FLIPPER);
 send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_FLIPPER_BASE);
 move_to_X_and_Z(X_POS_STACK_1, Z_POS_STORE_TOP); // go above storage position 1
 HAL_Delay(1500);
 set_Rotate_Servo(ROTATE_TO_STORE);
 HAL_Delay(500);

 move_to_X_and_Z(X_POS_STACK_1, Z_POS_STORE_6); // go down to pick token from position 6 of storage 1
 HAL_Delay(1500);

 move_to_X_and_Z(X_POS_STACK_1, Z_POS_STORE_TOP); // go up again
 HAL_Delay(500);

 send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_FLIPPER);
 send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_FLIPPER_BASE);
 move_to_X_and_Z(X_POS_STACK_2, Z_POS_STORE_TOP); // go above storage position 2
 HAL_Delay(1500);
 set_Rotate_Servo(ROTATE_TO_STORE);
 HAL_Delay(500);

 move_to_X_and_Z(X_POS_STACK_2, Z_POS_STORE_6); // go down to pick token from position 6 of storage 2
 HAL_Delay(1500);

 move_to_X_and_Z(X_POS_STACK_2, Z_POS_STORE_TOP); // go up again
 HAL_Delay(500);

 send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_FLIPPER);
 send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_FLIPPER_BASE);
 move_to_X_and_Z(X_POS_STACK_3, Z_POS_STORE_TOP); // go above storage position 3
 HAL_Delay(1500);
 set_Rotate_Servo(ROTATE_TO_STORE);
 HAL_Delay(500);

 move_to_X_and_Z(X_POS_STACK_3, Z_POS_STORE_6);// go down to pick token from position 6 of storage 2
 HAL_Delay(1500);

 move_to_X_and_Z(X_POS_STACK_3, Z_POS_STORE_TOP); // go up again
 HAL_Delay(500);
 */
