/*
 * colour_sensor.c
 * Hardware Device:TCS3472.c
 *
 *  Created on: 26 May 2023
 *      Author: Boris Ivanov
 */

#include "level_3/colour_sensor.h"

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
#define RGB_COMMAND_REG 0x80 // When sending commands, always set RGB_COMMAND_REG bit

#define RGB_REG_ENABLE 0x00
#define RGB_REG_TIMING 0x01
#define RGB_REG_CONTROL 0x0F // doesn't seem to be used anywhere as of yet

#define RGB_RED_LOW 0x16 	/* Red channel data */
#define RGB_RED_HIGH 0x17
#define RGB_GREEN_LOW 0x18 	/* Green channel data */
#define RGB_GREEN_HIGH 0x19
#define RGB_BLUE_LOW 0x1A 	/* Blue channel data */
#define RGB_BLUE_HIGH 0x1B
int red;
int yellow;
int rgb_error;

struct Color
{
	uint16_t r;
	uint16_t g;
	uint16_t b;
} Color;

TCS3472 TCS3472_Create(uint8_t addr, I2C_HandleTypeDef *handle)
/* Structure with the address and I2C handle of the RGB Sensor */
{
	//create structure of RBG sensor data
	TCS3472 sensor_data =
	{ addr, handle};
	return sensor_data;
}

void rgb_init(const TCS3472 *const self)
{
	rgb_send(self, 0x80, 0x03); // command to turn on the device
	HAL_Delay(2);

	// Set timing register (ADC integration time)
	// Integration time can be set in steps of 2.4 ms.
	// 0xFF = 2.4 ms
	// 0x00 = 700 ms
	// 0xEE = 238; (256 - 238) * 2.4 = 43.2 ms
	rgb_send(self, 0x81, 0xEE); // command to program ATIME
	HAL_Delay(10);

}

int rgb_read_sensor(const TCS3472 *const self)
{
	struct Color sens_RGBOut;
	int robotCoin = -2; 		// arbitrary value
	int t_it_RGB = 0;			// integration time ?
	uint16_t hue = 0;

	// initiate sensor
	rgb_init(self);

	while (robotCoin == -2) // loop until we have reached the max
	{
		sens_RGBOut = queryRGBSensor(self);

		// get hue value (dominant wavelength) out of RGB sensor readings
		hue = getHue(sens_RGBOut.r, sens_RGBOut.g, sens_RGBOut.b);

		if (hue >= 35 && hue <= 75)
		{
			// it is yellow
			robotCoin = 0;
			yellow++;
		}
		if (hue >= 340 && hue <= 360)
		{
			// it is red
			robotCoin = 1;
			red++;
		}

		t_it_RGB++;
		HAL_Delay(2);
		if (t_it_RGB > 24)
		{
			robotCoin = 3;
			rgb_error++;
		}
	}
	return robotCoin;
}

void rgb_send(const TCS3472 *const self, uint8_t regAddress, uint8_t data)
/*	rgb_send: Function which sends commands to the RGB sensor
 *
 * @param1 self: the structure which holds information about the RGB sensor
 * @param2 regAddress: the register to which the data will be written to
 * @param3 data: the data to be written in the register
 */
{
	i2c_Transmit(self->handle, self->dev_addr, regAddress, 1, &data, 1);
}

/**
 * queryRGBSensor: retrieve information from sensor
 *
 * Retrieves 16-bit number for red, green and blue
 *
 * Returns:
 * 	Color struct containing r, g and b
 */
struct Color queryRGBSensor(const TCS3472 *const self)
{

	/* Read RGB values */
	uint8_t low = 0; // temporary
	uint8_t high = 0; // temporary
	HAL_StatusTypeDef dev_Status;
	struct Color color;

	// Read red value
	dev_Status = i2c_Receive(self->handle, self->dev_addr, RGB_COMMAND_REG | RGB_RED_LOW, 1, &low, sizeof(low));
	dev_Status = i2c_Receive(self->handle, self->dev_addr, RGB_COMMAND_REG | RGB_RED_HIGH, 1, &high, sizeof(high));

	if (dev_Status != HAL_OK)
	{
		color.r = 0;
	}
	else
	{
		color.r = (high << 8) | low;
	}

	// Read green value
	i2c_Receive(self->handle, self->dev_addr, RGB_COMMAND_REG | RGB_GREEN_LOW, 1, &low, sizeof(low));
	i2c_Receive(self->handle, self->dev_addr, RGB_COMMAND_REG | RGB_GREEN_HIGH, 1, &high, sizeof(high));
	if (dev_Status != HAL_OK)
	{
		color.g = 0;
	}
	else
	{
		color.g = (high << 8) | low;
	}

	// Read blue value
	i2c_Receive(self->handle, self->dev_addr, RGB_COMMAND_REG | RGB_BLUE_LOW, 1, &low, sizeof(low));
	i2c_Receive(self->handle, self->dev_addr, RGB_COMMAND_REG | RGB_BLUE_HIGH, 1, &high, sizeof(high));
	if (dev_Status != HAL_OK)
	{
		color.b = 0;
	}
	else
	{
		color.b = (high << 8) | low;
	}
	return color;
}

/**
 * getHue: retrieve information from sensor
 *
 * Converts an RGB value to Hue spectrum (dominant wavelength)
 *
 * Inputs:
 * red:		red component of RGB
 * green:	green component of RGB
 * blue:	blue component of RGB
 *
 * Returns:
 * 	hue value in the range of 0 to 360
 */
uint16_t getHue(uint16_t red, uint16_t green, uint16_t blue)
{
	uint16_t max = max(max(red, green), blue);
	uint16_t min = min(min(red, green), blue);
	float hue = 0;

	// grey:
	if (min == max)
	{
		return 0;
	}

	if (max == red)
	{
		hue = (green - blue) / (float) (max - min);
	}
	else if (max == green)
	{
		hue = 2.0f + (blue - red) / (float) (max - min);
	}
	else
	{
		hue = 4.0f + (red - green) / (float) (max - min);
	}

	hue *= 60;
	// if hue is negative, add 360
	if (hue < 0)
		hue += 360;

	// round hue value and return
	return roundf(hue);
}

