/*
 * token_colour_separator.h
 *
 *  Created on: Apr 24, 2023
 *      Author: Boris Ivanov
 *
 *  Description: Handles all functions for the separation of tokens.
 */

#ifndef INC_LEVEL_2_TOKEN_COLOUR_SEPARATOR_H_
#define INC_LEVEL_2_TOKEN_COLOUR_SEPARATOR_H_

#include "level_3/colour_sensor.h"
#include "peripheral_devices/gpio.h"

void separate_tokens(const TCS3472 *const self);

#endif /* INC_LEVEL_2_TOKEN_COLOUR_SEPARATOR_H_ */
