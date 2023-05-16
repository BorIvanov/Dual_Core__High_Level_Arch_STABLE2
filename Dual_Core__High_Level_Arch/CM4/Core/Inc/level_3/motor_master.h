/*
 * motor_master.h
 *
 *  Created on: Jun 20, 2022
 *      Author: Pascal
 */

#ifndef INC_MOTOR_MASTER_H_
#define INC_MOTOR_MASTER_H_

#include "level_3/motor_x.h"
#include "level_3/motor_z.h"
#include "peripheral_devices/tim.h"
#include "peripheral_devices/gpio.h"
#include "peripheral_devices/usart.h"

#include <stdlib.h>


void initMotors();

uint8_t move_to_X_and_Z(int16_t posX, int16_t posZ);

uint8_t HomeMotors(uint8_t homeX, uint8_t homeZ);

#endif /* INC_MOTOR_MASTER_H_ */
