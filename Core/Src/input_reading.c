/*
 * input_reading.c
 *
 *  Created on: Oct 24, 2026
 *      Author: ducanhngo
 */

#include "input_reading.h" //task 5

#define DURATION_FOR_AUTO_INCREASING 100
#define BUTTON_PRESSED GPIO_PIN_RESET
#define BUTTON_RELEASED GPIO_PIN_SET

static GPIO_PinState buttonBuffer[BUTTON_NUM] = {BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED};
static GPIO_PinState debounceButtonBuffer1[BUTTON_NUM] = {BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED};
static GPIO_PinState debounceButtonBuffer2[BUTTON_NUM] = {BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED};
static GPIO_PinState debounceButtonBuffer3[BUTTON_NUM] = {BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED};
static uint8_t button_last_state[BUTTON_NUM] = {
    BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED
};
static uint8_t flagforbuttonpress1s[BUTTON_NUM];
static uint8_t counterforbuttonpress1s[BUTTON_NUM];

static uint16_t button_pins[BUTTON_NUM] = {BUT1_Pin,BUT2_Pin,BUT3_Pin};
static GPIO_TypeDef* button_ports[BUTTON_NUM] = {BUT1_GPIO_Port, BUT2_GPIO_Port, BUT3_GPIO_Port};

void button_reading(void){
	for(int i =0; i<BUTTON_NUM;i++){
		debounceButtonBuffer3[i] = debounceButtonBuffer2[i];
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(button_ports[i], button_pins[i]);

		        if ((debounceButtonBuffer1[i] == debounceButtonBuffer2[i]) &&
		                    (debounceButtonBuffer2[i] == debounceButtonBuffer3[i])) {

		                    buttonBuffer[i] = debounceButtonBuffer1[i];

		                    if (buttonBuffer[i] == BUTTON_PRESSED) {
		                        if (counterforbuttonpress1s[i] < DURATION_FOR_AUTO_INCREASING) {
		                            counterforbuttonpress1s[i]++;
		                        } else {
		                        	flagforbuttonpress1s[i] = 1;
		                        }
		                    } else {
		                    	counterforbuttonpress1s[i] = 0;
		                        flagforbuttonpress1s[i] = 0;
		                    }
		                }
	}
}

unsigned char is_button_pressed(unsigned char index){
	if(index >=BUTTON_NUM) return 0;
	return (buttonBuffer[index]==BUTTON_PRESSED);
}

unsigned char is_button_pressed_1s(unsigned char index){
	if(index >=BUTTON_NUM) return 0;
	return (flagforbuttonpress1s[index]==1);
}

unsigned char is_button_clicked(unsigned char index) {
    if (index >= BUTTON_NUM) return 0;

    if (buttonBuffer[index] == BUTTON_PRESSED &&
        button_last_state[index] == BUTTON_RELEASED) {
        button_last_state[index] = BUTTON_PRESSED;
        return 1;
    }
    else if (buttonBuffer[index] == BUTTON_RELEASED) {
        button_last_state[index] = BUTTON_RELEASED;
    }
    return 0;
}
