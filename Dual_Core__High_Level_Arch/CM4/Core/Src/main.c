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
#include "peripheral_devices/tim.h"
#include "peripheral_devices/usart.h"
#include "peripheral_devices/gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "level_2/init_CM4.h"
#include "level_2/user_detector.h"
#include "level_2/token_colour_separator.h"

#include "level_3/motor_master.h"
#include "level_3/servo_controller.h"
#include "level_3/proximity_sensor.h"
#include "level_3/colour_sensor.h"

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

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
	init_Start_Up();

	/* TODO: Move to global vars */
	//uint16_t value_proxy = 0;
	int columnDetected = 0;

	//VCNL4010 struct_proxy;
	TCS3472 struct_rgb;

	struct_rgb = TCS3472_Create(RGB_ADD, &hi2c1);
	rgb_init(&struct_rgb);
	init_coinDetector();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_STACK_3);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_STORE_TOP);
		move_to_X_and_Z(X_POS_STACK_3, Z_POS_STORE_TOP); // moves to above storage number 3
		HAL_Delay(1500);
		set_Rotate_Servo(ROTATE_TO_STORE); 				// rotates end-effector down
		HAL_Delay(500);

		move_to_X_and_Z(X_POS_STACK_3, Z_POS_STORE_6); 	// moves down to place token
		HAL_Delay(1500);

		move_to_X_and_Z(X_POS_STACK_3, Z_POS_STORE_TOP); // moves to above storage number 3 (goes back  up safely)
		HAL_Delay(500);

		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_COL_1);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_TOP);
		move_to_X_and_Z(X_POS_COL_1, Z_POS_TOP); 	// Moving above col 1 and going down to drop token
		HAL_Delay(1000);
		set_Rotate_Servo(ROTATE_TO_DROP);			// rotate to dropping position for the board
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_1, Z_POS_DROP); 	// moves to drops token in the board
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_1, Z_POS_TOP);	// moves back up
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_2, Z_POS_TOP);	// moves to position 2
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_2, Z_POS_DROP);	// moves to drop token in the board
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_2, Z_POS_TOP);	// moves back up
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_3, Z_POS_TOP);	// moves to position 3
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_3, Z_POS_DROP);	// moves to drop token in the board
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_3, Z_POS_TOP);	// moves back up
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_4, Z_POS_TOP);	// moves to position 4
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_4, Z_POS_DROP);	// moves to drop token in the board
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_4, Z_POS_TOP);	// moves back up
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_5, Z_POS_TOP);	// moves to position 5
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_5, Z_POS_DROP);	// moves to drop token in the board
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_5, Z_POS_TOP);	// moves back up
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_6, Z_POS_TOP);	// moves to position 6
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_6, Z_POS_DROP);	// moves to drop token in the board
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_6, Z_POS_TOP);	// moves back up
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_7, Z_POS_TOP);	// moves to position 7
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_7, Z_POS_DROP);	// moves to drop token in the board
		HAL_Delay(500);
		move_to_X_and_Z(X_POS_COL_7, Z_POS_TOP);	// moves back up
		HAL_Delay(1000);
		set_Rotate_Servo(ROTATE_NEUTRAL);
		HAL_Delay(500);

		// THIS order of opening has to be preserved
		send_msg((uint8_t*)"\rOpening Column 2\n\r");
		set_Slide_Servo(OPEN_COL_2);
		HAL_Delay(1000);

		send_msg((uint8_t*)"\rOpening Column 6\n\r");
		set_Slide_Servo(OPEN_COL_6);
		HAL_Delay(1000);

		send_msg((uint8_t*)"\rOpening Column 7\n\r");
		set_Slide_Servo(OPEN_COL_7);
		HAL_Delay(1000);

		send_msg((uint8_t*)"\rOpening Column 4\n\r");
		set_Slide_Servo(OPEN_COL_4);
		HAL_Delay(1000);

		send_msg((uint8_t*)"\rOpening Column 1\n\r");
		set_Slide_Servo(OPEN_COL_1);
		HAL_Delay(1000);

		send_msg((uint8_t*)"\rOpening Column 5\n\r");
		set_Slide_Servo(OPEN_COL_5);
		HAL_Delay(1000);

		send_msg((uint8_t*)"\rOpening Column 3\n\r");
		set_Slide_Servo(OPEN_COL_3);
		HAL_Delay(1000);

		send_msg((uint8_t*)"\rOpening board fully\n\r");
		set_Slide_Servo(SLIDE_OPEN);
		HAL_Delay(1500);

		send_msg((uint8_t*)"\rClosing board fully\n\r");
		set_Slide_Servo(SLIDE_CLOSED);
		HAL_Delay(1000);

		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_DUMP_BASE);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_DUMP_BASE);
		move_to_X_and_Z(X_POS_DUMP_BASE, Z_POS_DUMP_BASE);	// moves to above dump (clean-up task)
		HAL_Delay(1500);

		set_Rotate_Servo(ROTATE_TO_STACK); 					// move to picking up position (maybe rename define)
		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_DUMP_BASE);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_DUMP_2);
		move_to_X_and_Z(X_POS_DUMP_BASE, Z_POS_DUMP_2); 	// goes down to pick up a token
		HAL_Delay(1500);

		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_DUMP_BASE);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_DUMP_BASE);
		move_to_X_and_Z(X_POS_DUMP_BASE, Z_POS_DUMP_BASE);	// goes out of dump shoot
		HAL_Delay(1500);

		send_msg_data((uint8_t*)"\r##### Moving to pos X: %d #####\n\r", X_POS_FLIPPER);
		send_msg_data((uint8_t*)"\r##### Moving to pos Z: %d #####\n\r", Z_POS_FLIPPER_BASE);
		move_to_X_and_Z(X_POS_FLIPPER, Z_POS_FLIPPER_BASE);	// go above the RGB sensor
		HAL_Delay(1500);

		move_to_X_and_Z(X_POS_FLIPPER, Z_POS_FLIPPER); // go down to drop token
		HAL_Delay(1500);

		move_to_X_and_Z(X_POS_FLIPPER, Z_POS_FLIPPER_BASE); // go up
		HAL_Delay(500);


		separate_tokens(&struct_rgb); // colour detecting
		HAL_Delay(5000);
		separate_tokens(&struct_rgb); // colour detecting
		HAL_Delay(5000);
		separate_tokens(&struct_rgb); // colour detecting
		HAL_Delay(5000);


		columnDetected = queryLightGate(); // check columns
		send_msg_data((uint8_t*)"\r***** Column %d is blocked *****\n\r", columnDetected);
		HAL_Delay(5000);
		columnDetected = queryLightGate(); // check columns
		send_msg_data((uint8_t*)"\r***** Column %d is blocked *****\n\r", columnDetected);
		HAL_Delay(5000);
		columnDetected = queryLightGate(); // check columns
		send_msg_data((uint8_t*)"\r***** Column %d is blocked *****\n\r", columnDetected);
		HAL_Delay(5000);

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

	send_msg("\rERROR, resetting\n\r");

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
