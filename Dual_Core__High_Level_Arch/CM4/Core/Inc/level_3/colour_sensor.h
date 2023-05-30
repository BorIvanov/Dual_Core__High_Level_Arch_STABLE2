/*
 * colour_sensor.h
 *
 *  Created on: 7 dec. 2022
 *      Author: laure
 *
 *  Description: Requests data from the sensor TCS3472.
 */

#ifndef INC_colour_sensor_H_
#define INC_colour_sensor_H_

#include <stdint.h>
#include <stdlib.h>

#include "peripheral_devices/i2c.h"


#define RBG_BUS 0x29

typedef struct TCS3472
{
	uint8_t dev_addr;
	I2C_HandleTypeDef *handle;
} TCS3472;

void rgb_init(const TCS3472 *const self);

int rgb_read_sensor(const TCS3472 *const self);

void rgb_send(const TCS3472 *const self, uint8_t regAddress, uint8_t data);

uint16_t getHue(uint16_t red, uint16_t green, uint16_t blue);

TCS3472 TCS3472_Create(uint8_t addr, I2C_HandleTypeDef *handle);

struct Color queryRGBSensor(const TCS3472 *const self);

#endif /* INC_colour_sensor_H_ */
