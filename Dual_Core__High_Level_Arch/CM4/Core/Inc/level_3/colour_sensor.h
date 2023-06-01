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
#include "peripheral_devices/usart.h"

/* Define macro that finds maximum of two numbers */
#define max(a, b) \
	({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

/* Define macro that finds minimum of two numbers */
#define min(a, b) \
	({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

/* Define thresholds for colour recognition */
#define ROBOT_RED_LOWER 100
#define ROBOT_YELLOW_UPPER 100
#define HUMAN_RED_LOWER 200
#define HUMAN_YELLOW_LOWER 100
#define BLUE_UPPER 150

#define RGB_ENABLE_AIEN 0x10
#define RGB_ENABLE_AEN 0x02 // RGBC Enable - Writing 1 activates the ADC, 0 disables it
#define RGB_ENABLE_PON 0x01 // Power on - Writing 1 activates the internal oscillator, 0 disables it
#define RGB_COMMAND_REG 0x80 // When sending commands, always use RGB_COMMAND_REG as MSB

#define RGB_REG_ENABLE 0x00
#define RGB_REG_TIMING 0x01
#define RGB_REG_CONTROL 0x0F // doesn't seem to be used anywhere as of yet
#define RGB_ADD 0x29 		// address of the device

#define RGB_RED_LOW 0x16 	/* Red channel data */
#define RGB_RED_HIGH 0x17
#define RGB_GREEN_LOW 0x18 	/* Green channel data */
#define RGB_GREEN_HIGH 0x19
#define RGB_BLUE_LOW 0x1A 	/* Blue channel data */
#define RGB_BLUE_HIGH 0x1B

typedef struct TCS3472
{
	uint8_t dev_addr;
	I2C_HandleTypeDef *handle;
} TCS3472;

struct Color
{
	uint16_t r;
	uint16_t g;
	uint16_t b;
};

void rgb_init(const TCS3472 *const self);

int rgb_read_sensor(const TCS3472 *const self);

void rgb_send(const TCS3472 *const self, uint8_t regAddress, uint8_t data);

uint16_t getHue(uint16_t red, uint16_t green, uint16_t blue);

TCS3472 TCS3472_Create(uint8_t addr, I2C_HandleTypeDef *handle);

struct Color queryRGBSensor(const TCS3472 *const self);

#endif /* INC_colour_sensor_H_ */
