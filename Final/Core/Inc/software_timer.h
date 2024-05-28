/*
 * software_timer.h
 *
 *  Created on: May 5, 2024
 *      Author: Dell
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer1_flag;
extern int timer2_flag;
extern int timer3_flag;
extern int button_flag;
void setTimer1(int duration);
void setTimer2(int duration);
void setTimer3(int duration);
void setTimerButton(int duration);
void timerRun(void);
void ButtonTimer(void);

#endif /* INC_SOFTWARE_TIMER_H_ */
