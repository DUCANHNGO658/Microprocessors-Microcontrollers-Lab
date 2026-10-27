/*
 * timer.c
 *
 *  Created on: Oct 24, 2026
 *      Author: ducanhngo
 */
#include "main.h"
#include "input_reading.h"
#include "timer.h"
#define MAX_TIMERS 5

static int timer_counter[MAX_TIMERS];
static int timer_flags[MAX_TIMERS];

void setTimer(int index, int duration){
	timer_counter[index] = duration/TIMER_CYCLE;
	timer_flags[index] =0;


}

void timerRun(void){
	for(int i =0; i< MAX_TIMERS;i++){
		if(timer_counter[i]>0){
			timer_counter[i]--;
		if(timer_counter[i]<=0)
			timer_flags[i]=1;
	}
	}
}

int timerExpired(int index){
	if(timer_flags[index]==1){
		timer_flags[index]=0;
		return 1;
	}
	return 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
if(htim->Instance == TIM2){
button_reading();
timerRun();
}
}
