/*
 * software_timer.c
 *
 *  Created on: May 5, 2024
 *      Author: Dell
 */

#include "software_timer.h"
#define TICK 1

int timer1_counter =0;
int timer1_flag = 0;
int timer2_counter =0;
int timer2_flag = 0;
int timer3_counter =0;
int timer3_flag = 0;
int button_counter = 0;
int button_flag = 0;
void setTimer1(int duration){
	timer1_counter = duration/TICK;
	timer1_flag = 0;

}
void clearTimer1(){
	timer1_counter = 0;
	timer1_flag =0;
}
void setTimer2(int duration){
	timer2_counter = duration/TICK;
	timer2_flag = 0;

}
void clearTimer2(){
	timer2_counter = 0;
	timer2_flag =0;
}
void setTimer3(int duration){
	timer3_counter = duration/TICK;
	timer3_flag = 0;

}
void clearTimer3(){
	timer3_counter = 0;
	timer3_flag =0;
}
void setTimerButton(int duration){
	button_counter = duration/TICK;
	button_flag = 0;

}
void clearTimerButton(){
	button_counter = 0;
	button_flag =0;
}
void timerRun(){
	if(timer1_counter > 0){
		timer1_counter --;
		if(timer1_counter <= 0){
			timer1_flag = 1;
		}
	}
	if(timer2_counter > 0){
			timer2_counter --;
			if(timer2_counter <= 0){
				timer2_flag = 1;
			}
		}
	if(timer3_counter > 0){
				timer3_counter --;
				if(timer3_counter <= 0){
					timer3_flag = 1;
				}
			}

}
void ButtonTimer(){
	if(button_counter > 0){
			button_counter --;
						if(button_counter <= 0){
							button_flag = 1;
						}
					}
}
