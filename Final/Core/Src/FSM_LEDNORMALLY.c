/*
 * FSM_LEDNORMALLY.c
 *
 *  Created on: May 6, 2024
 *      Author: Admin
 */

#include "FSM_LEDNORMALLY.h"
#include "button.h"
#include "main.h"
#include "Dis7SEG.h"
#include "ModifyLED.h"
int isSetClear = 1;

int isButtonPressed();
int Counter = 5;
void SetTime (){
	status = 0;
			setTimer2(1000);
}
void fsm_simple_buttons_run(){

	if(isButtonPressed(&button1)){
		Counter = 0;
		SetTime();
	}
	if(isButtonPressed(&button2)){
			Counter++;

			SetTime();
		}
	if(isButtonPressed(&button3)){

			Counter--;
			SetTime();
	}
	if(button2.button1_flag ==2){
		if(timer1_flag == 1 ){
			Counter++;
			button2.button1_flag =0;

			SetTime();

		}
	}
	if(button3.button1_flag ==2){
			if(timer1_flag == 1 ){
				Counter--;
				button3.button1_flag =0;
				SetTime();

			}
		}
	if(Counter > 9) Counter = 0;
	if(Counter < 0) Counter = 9;
	display7SEG(Counter);

	if(timer2_flag == 1){
		status = 1;
		setTimer1(100);
		setTimer2(1000);
	}
}
void CounterDown(){
	if(timer1_flag == 1){
		if(Counter >0)
		Counter--;
		else Counter  = 0;
			setTimer1(100);
		}

	display7SEG(Counter);

	if(Counter == 0){
		setTimer2(1000);
		fsm_simple_buttons_run();
	}

}
void STM_Manager(){
	switch(status){
	case 0 :
		fsm_simple_buttons_run();
		break;
	case 1 :
		CounterDown();
		break;
	}
}



