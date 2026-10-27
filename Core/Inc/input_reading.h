/*
 * input_reading.h
 *
 *  Created on: Oct 24, 2026
 *      Author: ducanhngo
 */

#ifndef INC_INPUT_READING_H_ //task 5
#define INC_INPUT_READING_H_
#include "main.h"
#define BUTTON_NUM 3
void button_reading(void);
unsigned char is_button_pressed(unsigned char index);
unsigned char is_button_pressed_1s(unsigned char index);
unsigned char is_button_clicked(unsigned char index);
#endif /* INC_INPUT_READING_H_ */
