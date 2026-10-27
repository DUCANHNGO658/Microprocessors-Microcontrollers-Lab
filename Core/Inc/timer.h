/*
 * timer.h
 *
 *  Created on: Oct 24, 2026
 *      Author: ducanhngo
 */


#ifndef INC_TIMER_H
#define INC_TIMER_H

#define TIMER_CYCLE 10
void setTimer(int index, int duration_ms);
void timerRun(void);
int timerExpired(int index);

#endif
