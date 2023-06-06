/*
 * user_detector.h
 *
 *  Created on: Apr 24, 2023
 *      Author: Boris Ivanov
 *
 *  Description: Implements all functions for detecting when and where the user drops a token.
 */

#ifndef INC_LEVEL_2_USER_DETECTOR_H_
#define INC_LEVEL_2_USER_DETECTOR_H_

#include "main.h"
#include "level_2/init_CM4.h"
#include "peripheral_devices/usart.h"
#include "peripheral_devices/i2c.h"
#include "level_2/vars.h"

#define NumberOfStorages 3
#define NumberOfBoardColumns 7
#define NumberOfBoardRows 6
#define CD_ADD 0x38

int coinInsertDetection(void);
int whatStackToFill(void);
int whatStackToEmpty(void);
int queryLightGate(void);
int checkcoin(void);
void init_coinDetector(void);

//coinDetect/input fails
int detect_error = 0;

// Saves which gate the last thrown in coin was in.
int gateOld;



#endif /* INC_LEVEL_2_USER_DETECTOR_H_ */
