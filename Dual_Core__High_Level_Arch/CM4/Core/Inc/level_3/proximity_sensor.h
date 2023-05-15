/*
 * proximity_sensor.h
 * Hardware Device: VCNL4010
 *
 *  Created on: May 2, 2022
 *      Author: Pascal
 *
 *  Description: Receives data if a token is present.
 */

#ifndef INC_proximity_sensor_H_
#define INC_proximity_sensor_H_

#include <stdint.h>
#include <stdlib.h>

#include "peripheral_devices/i2c.h"

#define VCNL4010_COM_REG 0x80
//#define VCNL4010_COM_ENABLE 0x3
#define VCNL4010_LED_REG 0x83
//#define VCNL4010_LED_mA 0x0A
#define VCNL4010_PROXY_REG 0x87

typedef struct VCNL4010 {
	uint8_t base_addr;
	I2C_HandleTypeDef* bus;
} VCNL4010;

void VCNL4010_Init(const VCNL4010* const self);

uint16_t VCNL4010_ReceiveProxy(const VCNL4010* const self);

void VCNL4010_Transmit(const VCNL4010* const self, uint8_t data_reg, uint8_t data_size, uint8_t pData, uint8_t pData_size);

VCNL4010 VCNL4010_Create(uint8_t addr, I2C_HandleTypeDef* inBus);

#endif /* INC_proximity_sensor_H_ */
