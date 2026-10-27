/*
 * led_display.c
 *
 *  Created on: Oct 24, 2026
 *      Author: ducanhngo
 */

#include "main.h"
static int led_buffer[4] ={0,0,0,0};
void set_led_buffer(int digit0, int digit1, int digit2, int digit3) {
	led_buffer[0] = digit0;
	led_buffer[1] = digit1;
	led_buffer[2] = digit2;
	led_buffer[3] = digit3;
}

void display7SEG(int num) {
    HAL_GPIO_WritePin(GPIOA, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
                           |SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_SET);

    switch (num) {
        case 0: // a, b, c, d, e, f
            HAL_GPIO_WritePin(GPIOA, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin, GPIO_PIN_RESET);
            break;
        case 1: // b, c
            HAL_GPIO_WritePin(GPIOA, SEG1_Pin|SEG2_Pin, GPIO_PIN_RESET);
            break;
        case 2: // a, b, d, e, g
            HAL_GPIO_WritePin(GPIOA, SEG0_Pin|SEG1_Pin|SEG3_Pin|SEG4_Pin|SEG6_Pin, GPIO_PIN_RESET);
            break;
        case 3: // a, b, c, d, g
            HAL_GPIO_WritePin(GPIOA, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin|SEG6_Pin, GPIO_PIN_RESET);
            break;
        case 4: // b, c, f, g
            HAL_GPIO_WritePin(GPIOA, SEG1_Pin|SEG2_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
            break;
        case 5: // a, c, d, f, g
            HAL_GPIO_WritePin(GPIOA, SEG0_Pin|SEG2_Pin|SEG3_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
            break;
        case 6: // a, c, d, e, f, g
            HAL_GPIO_WritePin(GPIOA, SEG0_Pin|SEG2_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
            break;
        case 7: // a, b, c
            HAL_GPIO_WritePin(GPIOA, SEG0_Pin|SEG1_Pin|SEG2_Pin, GPIO_PIN_RESET);
            break;
        case 8:
            HAL_GPIO_WritePin(GPIOA, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
            break;
        case 9: // a, b, c, d, f, g
            HAL_GPIO_WritePin(GPIOA, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
            break;
        default:
            break;
    }
}


void update7SEG(int index){
    HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);

    switch(index){
        case 0:
            display7SEG(led_buffer[0]);
            HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_RESET);
            break;
        case 1:
            display7SEG(led_buffer[1]);
            HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_RESET);
            break;
        case 2:
            display7SEG(led_buffer[2]);
            HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_RESET);
            break;
        case 3:
            display7SEG(led_buffer[3]);
            HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_RESET);
            break;
        default:
            break;
    }
}

void clearAllTrafficLEDs(void){
	HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(AMBER_1_GPIO_Port, AMBER_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GREEN_1_GPIO_Port, GREEN_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RED_2_GPIO_Port, RED_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(AMBER_2_GPIO_Port, AMBER_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GREEN_2_GPIO_Port, GREEN_2_Pin, GPIO_PIN_SET);
}

void blinkRED2Hz(void){
	HAL_GPIO_WritePin(AMBER_1_GPIO_Port, AMBER_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GREEN_1_GPIO_Port, GREEN_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(AMBER_2_GPIO_Port, AMBER_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GREEN_2_GPIO_Port, GREEN_2_Pin, GPIO_PIN_SET);

HAL_GPIO_TogglePin(RED_1_GPIO_Port, RED_1_Pin);
HAL_GPIO_TogglePin(RED_2_GPIO_Port, RED_2_Pin);
}

void blinkAMBER2Hz(void){
	HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GREEN_1_GPIO_Port, GREEN_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RED_2_GPIO_Port, RED_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GREEN_2_GPIO_Port, GREEN_2_Pin, GPIO_PIN_SET);

HAL_GPIO_TogglePin(AMBER_1_GPIO_Port, AMBER_1_Pin);
HAL_GPIO_TogglePin(AMBER_2_GPIO_Port, AMBER_2_Pin);
}

void blinkGREEN2Hz(void){
	HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(AMBER_1_GPIO_Port, AMBER_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RED_2_GPIO_Port, RED_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(AMBER_2_GPIO_Port, AMBER_2_Pin, GPIO_PIN_SET);

HAL_GPIO_TogglePin(GREEN_1_GPIO_Port, GREEN_1_Pin);
HAL_GPIO_TogglePin(GREEN_2_GPIO_Port, GREEN_2_Pin);
}
