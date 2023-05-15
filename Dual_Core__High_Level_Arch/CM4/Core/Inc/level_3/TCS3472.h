/*
 * TCS3472.h
 *
 *  Created on: 7 dec. 2022
 *      Author: laure
 */

#ifndef INC_TCS3472_H_
#define INC_TCS3472_H_

#include <stdint.h>
#include <stdlib.h>

#include "peripheral_devices/i2c.h"

#define TCS3472_STATUS_REG 0x13
#define TCS3472_RED_LOW_REG 0x16
#define TCS3472_RED_HIGH_REG 0x17
#define TCS3472_GREEN_LOW_REG 0x18
#define TCS3472_GREEN_HIGH_REG 0x19
#define TCS3472_BLUE_LOW_REG 0x1A
#define TCS3472_BLUE_HIGH_REG 0x1B

typedef struct TCS3472
{
	uint8_t base_addr;
	I2C_HandleTypeDef *bus;
} TCS3472;

void TCS3472_Init(const TCS3472 *const self);

uint16_t TCS3472_ReceiveStatus(const TCS3472 *const self);

void TCS3472_Transmit(const TCS3472 *const self, uint8_t data_reg,
		uint8_t data_size, uint8_t pData, uint8_t pData_size);

TCS3472 TCS3472_Create(uint8_t addr, I2C_HandleTypeDef *inBus);

#endif /* INC_TCS3472_H_ */
