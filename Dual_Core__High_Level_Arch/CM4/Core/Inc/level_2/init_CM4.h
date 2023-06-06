/*
 * init_CM4.h
 *
 *  Created on: Apr 24, 2023
 *      Author: Boris Ivanov
 *
 *  Description:  Initialises and boots the Cortex-M4. In this phase, the
 *  sensors are tested for presence and the motors perform a "homing" protocol.
 */
#ifndef INC_LEVEL_2_INIT_CM4_H_
#define INC_LEVEL_2_INIT_CM4_H_

#include "peripheral_devices/tim.h"
#include "peripheral_devices/gpio.h"
#include "peripheral_devices/adc.h"
#include "peripheral_devices/usart.h"
#include "peripheral_devices/i2c.h"


#include "level_2/init_CM4.h"
#include "level_3/motor_master.h"
#include "level_3/servo_controller.h"
#include "main.h"


void start_PWM(void);
void init_Movement(void);
void init_MX_init(void);
void init_Start_Up(void);

#endif /* INC_LEVEL_2_INIT_CM4_H_ */
