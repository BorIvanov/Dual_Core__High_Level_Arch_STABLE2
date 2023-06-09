/*
 * colour_sensor.c
 * Hardware Device:TCS3472.c
 *
 *  Created on: 26 May 2023
 *      Author: Boris Ivanov
 */

#include "level_3/colour_sensor.h"

int red = 0;
int yellow = 0;
int rgb_error = 0;

TCS3472 TCS3472_Create(uint8_t addr, I2C_HandleTypeDef *handle)
/* Structure with the address and I2C handle of the RGB Sensor */
{
	//create structure of RBG sensor data
	TCS3472 sensor_data =
	{ addr, handle };
	return sensor_data;
}


void rgb_init(const TCS3472 *const self)
/* Function that programs the RGB sensor to turn on and then sets initial values */
{
	// command to turn on the device [0x03] sent to register [0x80]
	rgb_send(self, RGB_COMMAND_REG | RGB_REG_ENABLE,
			RGB_ENABLE_PON | RGB_ENABLE_AEN);

	HAL_Delay(2);

	// Set timing register (ADC integration time)
	// Integration time can be set in steps of 2.4 ms.
	// 0xFF = 2.4 ms
	// 0x00 = 700 ms
	// 0xEE = 238; (256 - 238) * 2.4 = 43.2 ms

	//  ATIME = 0xEE; sent to TIMING register [0x81]
	rgb_send(self, RGB_COMMAND_REG | RGB_REG_TIMING, 0xEE);
	HAL_Delay(10);
	send_msg((uint8_t*) "\r!RGB-Sensor Initialised!\n\r");

}

int rgb_read_sensor(const TCS3472 *const self)
/* rgb_read_sensor: Function which interprets the result from RGB sensor
 * legacy code
 * @param1 self: An address to the structure of the device
 *
 * RETURNS:
 * robotCoin = 0 --> The token is yellow
 * robotCoin = 1 --> The token is red
 * robotCoin = 3 --> The token is not present
 */
{
	struct Color sens_RGBOut;
	int robotCoin = -2; 		// arbitrary value to enter while loop
	int t_it_RGB = 0;			// integration time ? interrupt time ? Can't figure out name
	uint16_t hue = 0;

	while (robotCoin == -2) // loop until any return is reached
	{
		sens_RGBOut = queryRGBSensor(self); // store the structure of colours values from sens

		// get hue value (dominant wavelength) out of RGB sensor readings
		hue = getHue(sens_RGBOut.r, sens_RGBOut.g, sens_RGBOut.b);

		if (hue >= 35 && hue <= 75)
		{
			robotCoin = 0;
			yellow++;
		}
		if (hue >= 340 && hue <= 360)
		{
			robotCoin = 1;
			red++;
		}

		t_it_RGB++;
		HAL_Delay(2);
		if (t_it_RGB > 24)
		{
			// no token present
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

struct Color queryRGBSensor(const TCS3472 *const self)
/*
 * queryRGBSensor: retrieve information from sensor
 * Retrieves 16-bit number for red, green and blue
 *
 * @param1 self: An address to the structure of the device
 *
 * Returns:
 * 	Colour struct containing r, g and b
 */
{

	/* Read RGB values */
	uint8_t low = 0; // temporary
	uint8_t high = 0; // temporary
	HAL_StatusTypeDef dev_Status;
	struct Color color;

	// Read red value; LOW and HIGH channels
	dev_Status = i2c_Receive(self->handle, self->dev_addr,
			RGB_COMMAND_REG | RGB_RED_LOW, 1, &low, sizeof(low));
	dev_Status = i2c_Receive(self->handle, self->dev_addr,
			RGB_COMMAND_REG | RGB_RED_HIGH, 1, &high, sizeof(high));
	if (dev_Status != HAL_OK) // if device is not OK
	{
		color.r = 0; //output 0
	}
	else
	{
		color.r = (high << 8) | low; // combine both local values into the output struct
	}

	// Read green value; LOW and HIGH channels
	dev_Status = i2c_Receive(self->handle, self->dev_addr,
			RGB_COMMAND_REG | RGB_GREEN_LOW, 1, &low, sizeof(low));
	dev_Status = i2c_Receive(self->handle, self->dev_addr,
			RGB_COMMAND_REG | RGB_GREEN_HIGH, 1, &high, sizeof(high));
	if (dev_Status != HAL_OK) // if device is not OK
	{
		color.g = 0; //output 0
	}
	else
	{
		color.g = (high << 8) | low; // combine both local values into the output struct
	}

	// Read blue value; LOW and HIGH channels
	dev_Status = i2c_Receive(self->handle, self->dev_addr,
			RGB_COMMAND_REG | RGB_BLUE_LOW, 1, &low, sizeof(low));
	dev_Status = i2c_Receive(self->handle, self->dev_addr,
			RGB_COMMAND_REG | RGB_BLUE_HIGH, 1, &high, sizeof(high));
	if (dev_Status != HAL_OK) // if device is not OK
	{
		color.b = 0; //output 0
	}
	else
	{
		color.b = (high << 8) | low; // combine both local values into the output struct
	}
	return color;
}


uint16_t getHue(uint16_t red, uint16_t green, uint16_t blue)
/* getHue: retrieve information from sensor
 * legacy code
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

