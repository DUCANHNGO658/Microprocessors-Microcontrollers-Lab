/*
 * led_display.h
 *
 *  Created on: Oct 24, 2026
 *      Author: ducanhngo
 */


#ifndef INC_LED_DISPLAY_H
#define INC_LED_DISPLAY_H
#include "main.h"
void display7SEG(int num);
void update7SEG(int index);
void updateLEDMatrix(void);
void set_led_buffer(int digit0, int digit1, int digit2, int digit3);
void clearAllTrafficLEDs(void);
void blinkRED2Hz(void);
void blinkAMBER2Hz(void);
void blinkGREEN2Hz(void);

#endif
