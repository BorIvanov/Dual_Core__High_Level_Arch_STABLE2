/*
 * board_opener.c
 *
 *  Created on: Apr 24, 2023
 *      Author: Boris Ivanov
 */

#include "level_2/board_opener.h"

void open_all_columns(void)
{
	// THIS order of opening has to be preserved

	open_column_2(); 	// Opening Column 2

	open_column_6(); 	// Opening Column 6

	open_column_7();	// Opening Column 7

	open_column_4();	// Opening Column 4

	open_column_1();	// Opening Column 1

	open_column_5();	// Opening Column 5

	open_column_3();	// Opening Column 3

	open_fully();		// Opening the board fully

	close();			// Closing the board fully
}

void open_column_1(void)
{
	send_msg((uint8_t*) "\rOpening Column 1\n\r");
	set_Slide_Servo(OPEN_COL_1);
	HAL_Delay(OPENER_DELAY);
}

void open_column_2(void)
{
	send_msg((uint8_t*) "\rOpening Column 2\n\r");
	set_Slide_Servo(OPEN_COL_2);
	HAL_Delay(OPENER_DELAY);
}

void open_column_3(void)
{
	send_msg((uint8_t*) "\rOpening Column 3\n\r");
	set_Slide_Servo(OPEN_COL_3);
	HAL_Delay(OPENER_DELAY);
}

void open_column_4(void)
{
	send_msg((uint8_t*) "\rOpening Column 4\n\r");
	set_Slide_Servo(OPEN_COL_4);
	HAL_Delay(OPENER_DELAY);
}

void open_column_5(void)
{
	send_msg((uint8_t*) "\rOpening Column 5\n\r");
	set_Slide_Servo(OPEN_COL_5);
	HAL_Delay(OPENER_DELAY);
}

void open_column_6(void)
{
	send_msg((uint8_t*) "\rOpening Column 6\n\r");
	set_Slide_Servo(OPEN_COL_6);
	HAL_Delay(OPENER_DELAY);
}

void open_column_7(void)
{
	send_msg((uint8_t*) "\rOpening Column 7\n\r");
	set_Slide_Servo(OPEN_COL_7);
	HAL_Delay(OPENER_DELAY);
}

void open_fully(void)
{
	send_msg((uint8_t*) "\rOpening board fully\n\r");
	set_Slide_Servo(SLIDE_OPEN);
	HAL_Delay(OPENER_DELAY);
}

void close(void)
{
	send_msg((uint8_t*) "\rClosing board fully\n\r");
	set_Slide_Servo(SLIDE_CLOSED);
	HAL_Delay(OPENER_DELAY);
}

