/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "peripheral_devices/gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, DigiIN_OUT_Z_Pin|Direction_Z_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Ready_Z_GPIO_Port, Ready_Z_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, USB_OTG_FS_PWR_EN_Pin|DigiIN_OUT_X_Pin|Ready_X_Pin|Debug_1_Pin
                          |Debug_2_Pin|Debug_3_Pin|Debug_4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, Vaccuum_Valve_Pin|Vaccuum_Pump_Pin|Solenoid_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Enable_PWR_GPIO_Port, Enable_PWR_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Direction_X_GPIO_Port, Direction_X_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PEPin PEPin PEPin */
  GPIO_InitStruct.Pin = DigiIN_OUT_Z_Pin|Direction_Z_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin */
  GPIO_InitStruct.Pin = B1_Pin|Rotary_Switch_C2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = Rotary_Switch_C8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Rotary_Switch_C8_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = Ready_Z_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Ready_Z_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = Rotary_Switch_C1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Rotary_Switch_C1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = Rotary_Switch_C4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Rotary_Switch_C4_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = Homing_Z_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Homing_Z_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = Pushbutton_Rotary_Switch_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Pushbutton_Rotary_Switch_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PEPin PEPin PEPin */
  GPIO_InitStruct.Pin = Homing_X_Pin|Endstop_X_Pin|Endstop_Z_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PDPin PDPin PDPin PDPin
                           PDPin PDPin PDPin PDPin */
  GPIO_InitStruct.Pin = USB_OTG_FS_PWR_EN_Pin|DigiIN_OUT_X_Pin|Ready_X_Pin|Enable_PWR_Pin
                          |Debug_1_Pin|Debug_2_Pin|Debug_3_Pin|Debug_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin PCPin */
  GPIO_InitStruct.Pin = Vaccuum_Valve_Pin|Vaccuum_Pump_Pin|Solenoid_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin */
  GPIO_InitStruct.Pin = Coin_INT_Pin|Prox_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = Read_EMO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Read_EMO_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = Direction_X_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Direction_X_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
void set_Debug_1(void){
	HAL_GPIO_WritePin(Debug_1_GPIO_Port, Debug_1_Pin, GPIO_PIN_SET);
}
void reset_Debug_1(void){
	HAL_GPIO_WritePin(Debug_1_GPIO_Port, Debug_1_Pin, GPIO_PIN_RESET);
}

void set_Debug_2(void){
	HAL_GPIO_WritePin(Debug_2_GPIO_Port, Debug_2_Pin, GPIO_PIN_SET);
}
void reset_Debug_2(void){
	HAL_GPIO_WritePin(Debug_2_GPIO_Port, Debug_2_Pin, GPIO_PIN_RESET);
}

void set_Debug_3(void){
	HAL_GPIO_WritePin(Debug_3_GPIO_Port, Debug_3_Pin, GPIO_PIN_SET);
}
void reset_Debug_3(void){
	HAL_GPIO_WritePin(Debug_3_GPIO_Port, Debug_3_Pin, GPIO_PIN_RESET);
}

void set_Debug_4(void){
	HAL_GPIO_WritePin(Debug_4_GPIO_Port, Debug_4_Pin, GPIO_PIN_SET);
}
void reset_Debug_4(void){
	HAL_GPIO_WritePin(Debug_4_GPIO_Port, Debug_4_Pin, GPIO_PIN_RESET);
}



void set_LD1(void){
	HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
}
void reset_LD1(void){
	HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);

}

void set_LD2(void){
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
}
void reset_LD2(void){
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
}

void set_LD3(void){
	HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
}
void reset_LD3(void){
	HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
}



void set_Valve(void){
	HAL_GPIO_WritePin(Vaccuum_Valve_GPIO_Port, Vaccuum_Valve_Pin, GPIO_PIN_RESET);
}
void reset_Valve(void){
	HAL_GPIO_WritePin(Vaccuum_Valve_GPIO_Port, Vaccuum_Valve_Pin, GPIO_PIN_SET);
}

void set_Pump(void){
	HAL_GPIO_WritePin(Vaccuum_Pump_GPIO_Port, Vaccuum_Pump_Pin, GPIO_PIN_RESET);
}
void reset_Pump(void){
	HAL_GPIO_WritePin(Vaccuum_Pump_GPIO_Port, Vaccuum_Pump_Pin, GPIO_PIN_SET);
}

void set_Flipper(void){
	HAL_GPIO_WritePin(Solenoid_GPIO_Port, Solenoid_Pin, GPIO_PIN_RESET);
}
void reset_Flipper(void){
	HAL_GPIO_WritePin(Solenoid_GPIO_Port, Solenoid_Pin, GPIO_PIN_SET);
}



void set_Direction_X(void){
	HAL_GPIO_WritePin(Direction_X_GPIO_Port, Direction_X_Pin, GPIO_PIN_SET);
}
void reset_Direction_X(void){
	HAL_GPIO_WritePin(Direction_X_GPIO_Port, Direction_X_Pin, GPIO_PIN_RESET);
}

void set_Ready_X(void){
	HAL_GPIO_WritePin(Ready_X_GPIO_Port, Ready_X_Pin, GPIO_PIN_SET);
}
void reset_Ready_X(void){
	HAL_GPIO_WritePin(Ready_X_GPIO_Port, Ready_X_Pin, GPIO_PIN_RESET);
}

void set_Digout_X(void){
	HAL_GPIO_WritePin(DigiIN_OUT_X_GPIO_Port, DigiIN_OUT_X_Pin, GPIO_PIN_SET);
}
void reset_Digout_X(void){
	HAL_GPIO_WritePin(DigiIN_OUT_X_GPIO_Port, DigiIN_OUT_X_Pin, GPIO_PIN_RESET);
}



void set_Direction_Z(void){
	HAL_GPIO_WritePin(Direction_Z_GPIO_Port, Direction_Z_Pin, GPIO_PIN_SET);
}
void reset_Direction_Z(void){
	HAL_GPIO_WritePin(Direction_Z_GPIO_Port, Direction_Z_Pin, GPIO_PIN_RESET);
}

void set_Ready_Z(void){
	HAL_GPIO_WritePin(Ready_Z_GPIO_Port, Ready_Z_Pin, GPIO_PIN_SET);
}
void reset_Ready_Z(void){
	HAL_GPIO_WritePin(Ready_Z_GPIO_Port, Ready_Z_Pin, GPIO_PIN_RESET);
}

void set_Digout_Z(void){
	HAL_GPIO_WritePin(DigiIN_OUT_Z_GPIO_Port, DigiIN_OUT_Z_Pin, GPIO_PIN_SET);
}
void reset_Digout_Z(void){
	HAL_GPIO_WritePin(DigiIN_OUT_Z_GPIO_Port, DigiIN_OUT_Z_Pin, GPIO_PIN_RESET);
}



void set_Enable_Power(void){
	HAL_GPIO_WritePin(Enable_PWR_GPIO_Port, Enable_PWR_Pin, GPIO_PIN_RESET);
}
void reset_Enable_Power(void){
	HAL_GPIO_WritePin(Enable_PWR_GPIO_Port, Enable_PWR_Pin, GPIO_PIN_SET);
}

int get_Homing_X(void){
	return HAL_GPIO_ReadPin(Homing_X_GPIO_Port, Homing_X_Pin) == GPIO_PIN_RESET;
}
int get_Homing_Z(void){
	return HAL_GPIO_ReadPin(Homing_Z_GPIO_Port, Homing_Z_Pin) == GPIO_PIN_RESET;
}
int get_Endstop_X(void){
	return HAL_GPIO_ReadPin(Endstop_X_GPIO_Port, Endstop_X_Pin) == GPIO_PIN_RESET;
}
int get_Endstop_Z(void){
	return HAL_GPIO_ReadPin(Endstop_Z_GPIO_Port, Endstop_Z_Pin) == GPIO_PIN_RESET;
}

int get_Rotary_C1(void){
	return HAL_GPIO_ReadPin(Rotary_Switch_C1_GPIO_Port, Rotary_Switch_C1_Pin) == GPIO_PIN_SET;
}
int get_Rotary_C2(void){
	return HAL_GPIO_ReadPin(Rotary_Switch_C2_GPIO_Port, Rotary_Switch_C2_Pin) == GPIO_PIN_SET;
}
int get_Rotary_C4(void){
	return HAL_GPIO_ReadPin(Rotary_Switch_C4_GPIO_Port, Rotary_Switch_C4_Pin) == GPIO_PIN_SET;
}
int get_Rotary_C8(void){
	return HAL_GPIO_ReadPin(Rotary_Switch_C8_GPIO_Port, Rotary_Switch_C8_Pin) == GPIO_PIN_SET;

}
int get_Start_Selector(void){
	return HAL_GPIO_ReadPin(Pushbutton_Rotary_Switch_GPIO_Port, Pushbutton_Rotary_Switch_Pin) == GPIO_PIN_SET;
}
/* USER CODE END 2 */
