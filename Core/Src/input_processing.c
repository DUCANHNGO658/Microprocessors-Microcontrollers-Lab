/*
 * input_processing.c
 *
 *  Created on: Oct 24, 2026
 *      Author: ducanhngo
 */

#include "input_processing.h"
#include "input_reading.h"
#include "timer.h"
#include "led_display.h"

static int red_duration   = 6;
static int amber_duration = 2;
static int green_duration = 4;

static int temp_duration = 1;

static int current_digit_number = 0;

int current_mode = MODE_NORMAL;

typedef enum {
    AUTO_RED_GREEN,
    AUTO_RED_AMBER,
    AUTO_GREEN_RED,
    AUTO_AMBER_RED
} TrafficState;

static TrafficState traffic_state = AUTO_RED_GREEN;
static int count_way1 = 6;
static int count_way2 = 4;

static void update_traffic_leds(void) {
    switch (traffic_state) {
        case AUTO_RED_GREEN:
            HAL_GPIO_WritePin(GPIOB, RED_1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, AMBER_1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, GREEN_1_Pin, GPIO_PIN_SET);

            HAL_GPIO_WritePin(GPIOB, RED_2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, AMBER_2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, GREEN_2_Pin, GPIO_PIN_RESET);
            break;

        case AUTO_RED_AMBER:
            HAL_GPIO_WritePin(GPIOB, RED_1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, AMBER_1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, GREEN_1_Pin, GPIO_PIN_SET);

            HAL_GPIO_WritePin(GPIOB, RED_2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, AMBER_2_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, GREEN_2_Pin, GPIO_PIN_SET);
            break;

        case AUTO_GREEN_RED:
            HAL_GPIO_WritePin(GPIOB, RED_1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, AMBER_1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, GREEN_1_Pin, GPIO_PIN_RESET);

            HAL_GPIO_WritePin(GPIOB, RED_2_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, AMBER_2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, GREEN_2_Pin, GPIO_PIN_SET);
            break;

        case AUTO_AMBER_RED:
            HAL_GPIO_WritePin(GPIOB, RED_1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, AMBER_1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, GREEN_1_Pin, GPIO_PIN_SET);

            HAL_GPIO_WritePin(GPIOB, RED_2_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, AMBER_2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, GREEN_2_Pin, GPIO_PIN_SET);
            break;

        default:
            break;
    }
}

void fsm_for_input_processing(void) {
// TASK 5 & 9

    if (is_button_clicked(0)) {
        current_mode++;
        if (current_mode > 4) {
            current_mode = MODE_NORMAL;
        }

        clearAllTrafficLEDs();
        setTimer(0, 250);

        switch (current_mode) {
        case MODE_NORMAL:
                       traffic_state = AUTO_RED_GREEN;
                       count_way1 = red_duration;
                       count_way2 = green_duration;
                       update_traffic_leds();
                       setTimer(2, 1000);
                       break;

            case MODE_RED:
                temp_duration = red_duration;
                break;
            case MODE_AMBER:
                temp_duration = amber_duration;
                break;
            case MODE_GREEN:
                temp_duration = green_duration;
                break;
            default:
                break;
        }
    }

// TASK 7
    if (current_mode != MODE_NORMAL) {
        static int auto_inc_counter = 0;
        int trigger_inc = 0;

        if (is_button_clicked(1)) {
            trigger_inc = 1;
            auto_inc_counter = 0;
        } else if (is_button_pressed_1s(1)) {
            auto_inc_counter++;
            if (auto_inc_counter >= 20) {
                trigger_inc = 1;
                auto_inc_counter = 0;
            }
        } else {
            auto_inc_counter = 0;
        }

        if (trigger_inc) {
            temp_duration++;
            if (temp_duration > 99) {
                temp_duration = 1;
            }
        }
    }
 // TASK 8
    if (current_mode != MODE_NORMAL) {
        if (is_button_clicked(2)) {
            switch (current_mode) {
                case MODE_RED:
                    red_duration = temp_duration;
                    break;
                case MODE_AMBER:
                    amber_duration = temp_duration;
                    break;
                case MODE_GREEN:
                    green_duration = temp_duration;
                    break;
                default:
                    break;
            }
        }
    }

    if (current_mode != MODE_NORMAL) {
    	set_led_buffer(0, temp_duration / 10, current_mode, temp_duration % 10);
        if (timerExpired(0)) {
            setTimer(0, 250);
            switch (current_mode) {
                case MODE_RED:   blinkRED2Hz();   break;
                case MODE_AMBER: blinkAMBER2Hz(); break;
                case MODE_GREEN: blinkGREEN2Hz(); break;
                default: break;
            }
        }
    } else {
// TASK 10
    	set_led_buffer(count_way1 / 10, count_way2 / 10, count_way1 % 10, count_way2 % 10);

        if (timerExpired(2)) {
            setTimer(2, 1000);
            count_way1--;
            count_way2--;

            if (count_way1 <= 0 || count_way2 <= 0) {
                switch (traffic_state) {
                    case AUTO_RED_GREEN:
                        traffic_state = AUTO_RED_AMBER;
                        count_way2 = amber_duration;
                        break;

                    case AUTO_RED_AMBER:
                        traffic_state = AUTO_GREEN_RED;
                        count_way1 = green_duration;
                        count_way2 = red_duration;
                        break;

                    case AUTO_GREEN_RED:
                        traffic_state = AUTO_AMBER_RED;
                        count_way1 = amber_duration;
                        break;

                    case AUTO_AMBER_RED:
                        traffic_state = AUTO_RED_GREEN;
                        count_way1 = red_duration;
                        count_way2 = green_duration;
                        break;

                    default:
                        break;
                }
                update_traffic_leds();
            }
        }
    }
    if (timerExpired(1)) {
        setTimer(1, 10);
        update7SEG(current_digit_number);
        current_digit_number = (current_digit_number + 1) % 4;
    }
}
