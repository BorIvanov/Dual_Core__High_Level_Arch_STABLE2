/*
 * vars.h
 *
 *  Created on: 6 Jun 2023
 *      Author: Boris Ivanov
 */

#ifndef INC_LEVEL_2_VARS_H_
#define INC_LEVEL_2_VARS_H_

#define NumberOfStorages 3
#define NumberOfBoardColumns 7
#define NumberOfBoardRows 6

// storage, starts filled during game start!
unsigned int mem_StorageStack[NumberOfStorages];
// layout of the board
int mem_Board[NumberOfBoardColumns];
int mem_Board_old[NumberOfBoardColumns];
int sens = 1;

void initGlobalVars(void);


#endif /* INC_LEVEL_2_VARS_H_ */
