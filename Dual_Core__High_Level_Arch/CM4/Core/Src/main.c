/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
#include "main.h"
#include "peripheral_devices/usart.h"
#include "peripheral_devices/gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "level_2/init_CM4.h"

#include "level_3/motor_master.h"

#include "level_3/servo_controller.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* USER CODE BEGIN Boot_Mode_Sequence_1 */
	/*HW semaphore Clock enable*/
	__HAL_RCC_HSEM_CLK_ENABLE();
	/* Activate HSEM notification for Cortex-M4*/
	HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));
	/*
  Domain D2 goes to STOP mode (Cortex-M4 in deep-sleep) waiting for Cortex-M7 to
  perform system initialization (system clock config, external memory configuration.. )
	 */
	HAL_PWREx_ClearPendingEvent();
	HAL_PWREx_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFE, PWR_D2_DOMAIN);
	/* Clear HSEM flag */
	__HAL_HSEM_CLEAR_FLAG(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));

	/* USER CODE END Boot_Mode_Sequence_1 */
	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialise all configured peripherals */
	MX_GPIO_Init();
	MX_USART3_UART_Init();
	/* USER CODE BEGIN 2 */
	init_Start_Up();


	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		reset_Valve();

		// THIS order of opening has to be preserved
		set_Slide_Servo(OPEN_COL_2);
		HAL_Delay(1000);
		set_Slide_Servo(OPEN_COL_6);
		HAL_Delay(1000);
		set_Slide_Servo(OPEN_COL_7);
		HAL_Delay(1000);
		set_Slide_Servo(OPEN_COL_4);
		HAL_Delay(1000);
		set_Slide_Servo(OPEN_COL_1);
		HAL_Delay(1000);
		set_Slide_Servo(OPEN_COL_5);
		HAL_Delay(1000);
		set_Slide_Servo(OPEN_COL_3);
		HAL_Delay(1000);
		set_Slide_Servo(SLIDE_OPEN);
		HAL_Delay(1000);

		set_Slide_Servo(SLIDE_CLOSED);

		set_Rotate_Servo(ROTATE_NEUTRAL);
		HAL_Delay(1000);
		set_Rotate_Servo(ROTATE_TO_STACK);
		HAL_Delay(1000);
		set_Rotate_Servo(ROTATE_TO_DROP);
		HAL_Delay(1000);
		set_Rotate_Servo(ROTATE_NEUTRAL);

		HAL_Delay(2000);
		//testing direction X
		moveToPosX(30); // neutral - from Laurens
		HAL_Delay(500);
		moveToPosX(40);    // neutral - from Laurens
		HAL_Delay(500);
		moveToPosX(20);    // neutral - from Laurens
		HAL_Delay(500);
		//testing direction Z
		moveToPosZ(42); // neutral - from Laurens
		HAL_Delay(500);
		moveToPosZ(10); // neutral - from Laurens
		HAL_Delay(500);
		moveToPosZ(30); // neutral - from Laurens
		HAL_Delay(500);



		MoveToPos(46.67, 18);

		MoveToPos(46.67, 0);

		HAL_Delay(500);
		set_Pump();
		HAL_Delay(4000);
		set_Valve();
		while(GetVAC() < 2000){

		}
//		reset_Pump();
		MoveToPos(46.67, 18);
		set_Rotate_Servo(0.0);
		HAL_Delay(1000);
		reset_Valve();
		reset_Pump();
		HAL_Delay(1000);
		set_Rotate_Servo(0.45);
		HAL_Delay(1000);
		float i = 0.0;
		for(i = 0; i<1; i+=0.1){
			MoveToPos(46.67, 18);
			MoveToPos(46.67, 0);
			HAL_Delay(2000);
			set_Pump();
			HAL_Delay(4000);
			set_Valve();
			while(GetVAC() < 2000){

			}
//			reset_Pump();
			MoveToPos(46.67, 18);
			set_Rotate_Servo(0.0);
			HAL_Delay(1000);
			reset_Valve();
			reset_Pump();
			HAL_Delay(1000);
			set_Rotate_Servo(0.45);
			HAL_Delay(1000);
			set_Slide_Servo(i);
			HAL_Delay(3000);
		}
		while(1){

		}

	}
	/* USER CODE END 3 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();

	reset_Enable_Power();

	uint8_t send[16];
	sprintf(send, "ERROR, resetting");
	ST_LINK_WRITE(send, 16);
	NVIC_SystemReset();
	while (1)
	{

	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
