/*
 * ModifyLED.c
 *
 *  Created on: May 6, 2024
 *      Author: Admin
 */

#include "ModifyLED.h"
#include "global.h"
#include "button.h"
#include "FSM_LEDNORMALLY.h"
#include "Dis7SEG.h"

int currentTime = 0 ;
void OnModify(){
	if(status == MODIFY){
		if(currentTime > 99) currentTime=0;
		switch(LED){
		case RED:

			NumberDivision(currentTime);
			if(isButtonPressed(&button2)){
				NumberDivision(currentTime);
				currentTime++;
			}
			if(isButtonPressed(&button3)){
							SetLedTime(RED, currentTime);
							HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
						}
			if(timer1_flag==1){
				HAL_GPIO_TogglePin(GPIOA, LED_RED_Pin|LED_REDB_Pin);
				setTimer1(500);
			}
			if(isButtonPressed(&button1)){
				LED = YELLOW;
				currentTime = ledTime[YELLOW];
			}

			break;
		case YELLOW:

			NumberDivision(currentTime);
			if(isButtonPressed(&button2)){

				currentTime++;
				if(currentTime + ledTime[GREEN] <= ledTime[RED] )
				{


				}
				else {
					if(ledTime[RED] < 99 )
					{
						currentTime++;
						SetLedTime(RED, ++ledTime[RED]);
					}
				}
			}
			if(isButtonPressed(&button3)){

				if(currentTime + ledTime[GREEN] <= ledTime[RED] )
				{
					SetLedTime(YELLOW, currentTime);

				}
				else {
				if(ledTime[RED] < 99 )
				{
					SetLedTime(YELLOW, currentTime);
					SetLedTime(RED, currentTime + ledTime[GREEN]);
				}
			}
			}
			if(timer1_flag==1){
							HAL_GPIO_TogglePin(GPIOA, LED_YELLOW_Pin|LED_YELLOWB_Pin);
							setTimer1(500);
			}
			if(isButtonPressed(&button1)){
				LED = GREEN;
				currentTime = ledTime[GREEN];
			}
			break;
		case GREEN:

			NumberDivision(currentTime);
			if(isButtonPressed(&button2)){


					currentTime++;



			}
			if(isButtonPressed(&button3)){
				if(currentTime + ledTime[YELLOW] <= ledTime[RED] )
				{
					SetLedTime(GREEN, currentTime);

				}
				else {
					if(ledTime[RED] < 99 )
					{
						SetLedTime(GREEN, currentTime);
						SetLedTime(RED, currentTime + ledTime[YELLOW]);
					}
				}
			}
			if(timer1_flag==1){
							HAL_GPIO_TogglePin(GPIOA, LED_GREEN_Pin|LED_GREENB_Pin);
							setTimer1(500);
						}
			if(isButtonPressed(&button1)){
				LED = RED;
				status = AUTO_RED;
				isSetClear =1;
			}
			break;
		}
	}
}
