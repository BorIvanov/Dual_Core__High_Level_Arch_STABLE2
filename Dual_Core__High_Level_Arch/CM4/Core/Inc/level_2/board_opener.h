/*
 * board_opener.h
 *
 *  Created on: Apr 24, 2023
 *      Author: Boris Ivanov
 *
 *  Description: The Board opener implements all the functions for handling the opening of
 *  the Connect-4 board when the game is finished.
 */

#ifndef INC_LEVEL_2_BOARD_OPENER_H_
#define INC_LEVEL_2_BOARD_OPENER_H_

#include "level_3/servo_controller.h"
#include "peripheral_devices/usart.h"

#define OPENER_DELAY 750

void open_all_columns(void);
void open_column_1(void);
void open_column_2(void);
void open_column_3(void);
void open_column_4(void);
void open_column_5(void);
void open_column_6(void);
void open_column_7(void);
void open_fully(void);
void close(void);



#endif /* INC_LEVEL_2_BOARD_OPENER_H_ */
