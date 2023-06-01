/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    i2c.c
 * @brief   This file provides code for the configuration
 *          of the I2C instances.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "peripheral_devices/i2c.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

I2C_HandleTypeDef hi2c1;

/* I2C1 init function */
void MX_I2C1_Init(void)
{

	/* USER CODE BEGIN I2C1_Init 0 */

	/* USER CODE END I2C1_Init 0 */

	/* USER CODE BEGIN I2C1_Init 1 */

	/* USER CODE END I2C1_Init 1 */
	hi2c1.Instance = I2C1;
	hi2c1.Init.Timing = 0x307075B1;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
		Error_Handler();
	}

	/** Configure Analogue filter
	 */
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	{
		Error_Handler();
	}

	/** Configure Digital filter
	 */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN I2C1_Init 2 */

	/* USER CODE END I2C1_Init 2 */

}

void HAL_I2C_MspInit(I2C_HandleTypeDef *i2cHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct =
	{ 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct =
	{ 0 };
	if (i2cHandle->Instance == I2C1)
	{
		/* USER CODE BEGIN I2C1_MspInit 0 */

		/* USER CODE END I2C1_MspInit 0 */

		/** Initializes the peripherals clock
		 */
		PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
		PeriphClkInitStruct.I2c123ClockSelection = RCC_I2C123CLKSOURCE_D2PCLK1;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**I2C1 GPIO Configuration
		 PB8     ------> I2C1_SCL
		 PB9     ------> I2C1_SDA
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* I2C1 clock enable */
		__HAL_RCC_I2C1_CLK_ENABLE();
		/* USER CODE BEGIN I2C1_MspInit 1 */

		/* USER CODE END I2C1_MspInit 1 */
	}
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef *i2cHandle)
{

	if (i2cHandle->Instance == I2C1)
	{
		/* USER CODE BEGIN I2C1_MspDeInit 0 */

		/* USER CODE END I2C1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_I2C1_CLK_DISABLE();

		/**I2C1 GPIO Configuration
		 PB8     ------> I2C1_SCL
		 PB9     ------> I2C1_SDA
		 */
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8);

		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_9);

		/* USER CODE BEGIN I2C1_MspDeInit 1 */

		/* USER CODE END I2C1_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */
HAL_StatusTypeDef i2c_CheckDev(I2C_HandleTypeDef *bus, uint8_t DevAddress)
{
	HAL_StatusTypeDef retFunc;
	uint8_t write_addr = DevAddress << 1;
	retFunc = HAL_I2C_IsDeviceReady(bus, write_addr, 1, TIME_OUT);
	return retFunc;
}

HAL_StatusTypeDef i2c_Transmit(I2C_HandleTypeDef *bus, uint8_t DevAddress,
		uint8_t MemAddress, uint8_t MemAddSize, uint8_t *pData,
		uint8_t pData_size)
/* @brief Transmits data over I2C bus.
This function transmits data over the I2C bus using the specified parameters.

@param[1] bus: Pointer to the I2C_HandleTypeDef structure that contains
@param[2] DevAddress: Target device address.
@param[3] MemAddress: Memory address within the target device (register address).
@param[4] MemAddSize: Size of the memory address in bytes.
@param[5] pData: Pointer to the data buffer containing the data to be transmitted.
@param[6] pData_size: Size of the data buffer in bytes.

@retval HAL_StatusTypeDef: HAL status enumeration value.
 */
{
	HAL_StatusTypeDef retFunc;
	uint8_t write_addr = DevAddress << 1;
	retFunc = HAL_I2C_Mem_Write(bus, write_addr, MemAddress, MemAddSize, pData,
			pData_size, TIME_OUT);
	return retFunc;
}

HAL_StatusTypeDef i2c_Receive(I2C_HandleTypeDef *bus, uint8_t DevAddress,
		uint8_t MemAddress, uint8_t MemAddSize, uint8_t *pData,
		uint8_t pData_size)
/*
@brief Receives data over I2C bus.
This function receives data over the I2C bus using the specified parameters.

@param[1] bus: Pointer to the I2C_HandleTypeDef structure that contains
@param[2] DevAddress: Target device address.
@param[3] MemAddress: Memory address within the target device (register address).
@param[4] MemAddSize: Size of the memory address in bytes (can be 1 or 2).
@param[5] pData: Pointer to the data buffer to store the received data.
@param[6] pData_size: Size of the data buffer in bytes.

@retval HAL_StatusTypeDef: HAL status enumeration value.
 */
{
	HAL_StatusTypeDef retFunc;
	uint8_t read_addr = (DevAddress << 1) | 0x01;
	retFunc = HAL_I2C_Mem_Read(bus, read_addr, MemAddress, MemAddSize, pData,
			pData_size, TIME_OUT);
	return retFunc;
}
/* USER CODE END 1 */
