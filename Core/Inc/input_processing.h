/*
 * input_processing.h
 *
 *  Created on: Oct 24, 2026
 *      Author: ducanhngo
 */


#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_

#include "main.h"

// 4 state working
#define MODE_NORMAL 1 //task 5
#define MODE_RED 2
#define MODE_AMBER 3
#define MODE_GREEN 4

extern int current_mode;
void fsm_for_input_processing(void);
#endif /* INC_INPUT_PROCESSING_H_ */
