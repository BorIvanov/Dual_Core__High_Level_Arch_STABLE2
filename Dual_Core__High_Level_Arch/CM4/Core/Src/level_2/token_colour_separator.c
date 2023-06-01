/*
 * token_colour_separator.c
 *
 *  Created on: Apr 24, 2023
 *      Author: Boris Ivanov
 */

#include "level_2/token_colour_separator.h"

int separate_tokens(const TCS3472 *const self)
/* separate_tokens: Function which separates tokens to robot/user storage
 *
 * Shoots yellow token, or gives signal to move red token
 *
 */
{
	int value_rgb = 0;

	value_rgb = rgb_read_sensor(self); // store sensor readings

	switch (value_rgb)
	{
	case 0: 	// yellow token
		send_msg((uint8_t*)"\rThe colour of the token is YELLOW!\n\r");

		/* uncomment when FLIPPER is fixed
		set_Flipper();
		HAL_Delay(5);
		reset_Flipper();
		break;
		*/
		break;

	case 1: 	// red token
		send_msg((uint8_t*)"\rThe colour of the token is RED!\n\r");
		break;

	case 3:		// no token present
		send_msg((uint8_t*)"\rNo token is present!\n\r");
		break;

	default:
		send_msg((uint8_t*)"\rDEF:No token is present!\n\r");
		break;
	}
	return value_rgb;
}
