/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
void set_Debug_1(void);
void reset_Debug_1(void);

void set_Debug_2(void);
void reset_Debug_2(void);

void set_Debug_3(void);
void reset_Debug_3(void);

void set_Debug_4(void);
void reset_Debug_4(void);



void set_LD1(void);
void reset_LD1(void);

void set_LD2(void);
void reset_LD2(void);

void set_LD3(void);
void reset_LD3(void);



void set_Valve(void);
void reset_Valve(void);

void set_Pump(void);
void reset_Pump(void);

void set_Flipper(void);
void reset_Flipper(void);



void set_Direction_X(void);
void reset_Direction_X(void);

void set_Ready_X(void);
void reset_Ready_X(void);

void set_Digout_X(void);
void reset_Digout_X(void);



void set_Direction_Z(void);
void reset_Direction_Z(void);

void set_Ready_Z(void);
void reset_Ready_Z(void);

void set_Digout_Z(void);
void reset_Digout_Z(void);

void set_Enable_Power(void);
void reset_Enable_Power(void);

int get_Homing_X(void);
int get_Homing_Z(void);
int get_Endstop_X(void);
int get_Endstop_Z(void);

int get_Rotary_C1(void);
int get_Rotary_C2(void);
int get_Rotary_C4(void);
int get_Rotary_C8(void);
int get_Start_Selector(void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

