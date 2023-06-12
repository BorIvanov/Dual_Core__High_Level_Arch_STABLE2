/*
 * common.h
 *
 *  Created on: Apr 29, 2022
 *      Author: Pascal
 *  Edited on: June 12, 2023
 *      Author: Boris Ivanov
 */

#ifndef INC_COMMON_H_
#define INC_COMMON_H_

#include "stm32h7xx.h"

#define HSEM_TAKE_RELEASE(_id_)             do { HAL_HSEM_FastTake((_id_)); HAL_HSEM_Release((_id_), 0); } while (0)

#define HSEM_WAKEUP_CPU2                    0
#define HSEM_WAKEUP_CPU2_MASK               __HAL_HSEM_SEMID_TO_MASK(HSEM_WAKEUP_CPU2)

#define HSEM_CM4_TO_CM7                     29
#define HSEM_CM4_TO_CM7_MASK                __HAL_HSEM_SEMID_TO_MASK(HSEM_CM4_TO_CM7)
#define HSEM_CM7_TO_CM4                     30
#define HSEM_CM7_TO_CM4_MASK                __HAL_HSEM_SEMID_TO_MASK(HSEM_CM7_TO_CM4)
#define HSEM_ERROR		                    31
#define HSEM_ERROR_MASK		                __HAL_HSEM_SEMID_TO_MASK(HSEM_ERROR)

#define HSEM_CM4_DONE	                    1
#define HSEM_CM4_INIT	                    2
#define HSEM_USER_TURN	                    3
#define HSEM_ROBOT_TURN	                    4
#define HSEM_GAME_END	                    5
#define HSEM_CLEAN_UP	                    6
#define HSEM_CHEAT	                    	7

#define HSEM_CM4_DONE_MASK	                __HAL_HSEM_SEMID_TO_MASK(HSEM_CM4_DONE)
#define HSEM_CM4_INIT_MASK	                __HAL_HSEM_SEMID_TO_MASK(HSEM_CM4_INIT)
#define HSEM_USER_TURN_MASK	                __HAL_HSEM_SEMID_TO_MASK(HSEM_USER_TURN)
#define HSEM_ROBOT_TURN_MASK	            __HAL_HSEM_SEMID_TO_MASK(HSEM_ROBOT_TURN)
#define HSEM_GAME_END_MASK	                __HAL_HSEM_SEMID_TO_MASK(HSEM_GAME_END)
#define HSEM_CLEAN_UP_MASK	                __HAL_HSEM_SEMID_TO_MASK(HSEM_CLEAN_UP)
#define HSEM_CHEAT_MASK	                    __HAL_HSEM_SEMID_TO_MASK(HSEM_CHEAT)

static __attribute__ ((section(".SharedBuffer"), used)) uint8_t SharedBuf[10];

#endif /* INC_COMMON_H_ */
