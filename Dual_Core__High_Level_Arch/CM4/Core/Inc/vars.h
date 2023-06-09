/*
 * vars.h
 *
 *  Created on: Jun 6, 2023
 *      Author: Boris Ivanov
 */

#ifndef INC_VARS_H_
#define INC_VARS_H_

/* Defines */
#define NumberOfStorages 3
#define NumberOfBoardColumns 7
#define NumberOfBoardRows 6

/* Variables */
extern int mem_StorageStack[3];
extern int mem_Board[7];
extern int mem_Board_old[7];
extern int sens;
extern int Sens_CoinEntry;
extern int detect_error;	//coinDetect/input fails
extern int gateOld;			// Saves which gate the last thrown in coin was in.


/* Functions */
void initGlobalVars();

#endif /* INC_VARS_H_ */
