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
int Counter = 0;
void FSM_LedNormalRun(){
	switch(status){
	case INIT:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5|GPIO_PIN_7|GPIO_PIN_6, GPIO_PIN_SET);
		status = AUTO_RED;

		currentLedTime = ledTime[RED];
		setTimer1(500);
		setTimer2(1000);
		setTimer3(500);
		break;
	case AUTO_RED:
		HAL_GPIO_WritePin(GPIOA, LED_YELLOW_Pin|LED_GREEN_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED_RED_Pin, GPIO_PIN_RESET);
		//Display();
		if(isButtonPressed(&button1)){
			status = MODIFY;
			setTimer1(500);
			currentTime = ledTime[RED];
		}
		if(timer2_flag ==1){

					currentLedTime--;
					NumberDivision(currentLedTime);
					setTimer2(1000);
					Counter++;
					if(Counter <= ledTime[GREEN]){
						HAL_GPIO_WritePin(GPIOA, LED_REDB_Pin|LED_YELLOWB_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(GPIOA, LED_GREENB_Pin, GPIO_PIN_RESET);
					}
					else if(Counter <= ledTime[GREEN] + ledTime[YELLOW] ){
						HAL_GPIO_WritePin(GPIOA, LED_REDB_Pin|LED_GREENB_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(GPIOA, LED_YELLOWB_Pin, GPIO_PIN_RESET);
					}
					else Counter = 0;

				}
		if(timer1_flag ==1){
			status = AUTO_GREEN;
			currentLedTime = ledTime[GREEN];
			setTimer1(ledTime[GREEN]*1000);
			HAL_GPIO_WritePin(GPIOA, LED_YELLOWB_Pin|LED_GREENB_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, LED_REDB_Pin, GPIO_PIN_RESET);
		}



		break;
	case AUTO_YELLOW:
		HAL_GPIO_WritePin(GPIOA, LED_RED_Pin|LED_GREEN_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, LED_YELLOW_Pin, GPIO_PIN_RESET);
				//Display();
				if(timer1_flag ==1){
					HAL_GPIO_WritePin(GPIOA, LED_REDB_Pin, GPIO_PIN_SET);
					status = AUTO_RED;
					currentLedTime = ledTime[0];
					setTimer1(ledTime[0]*1000);
				}
				if(timer2_flag ==1){

					currentLedTime--;
					NumberDivision(currentLedTime);
					setTimer2(1000);

				}
				if(isButtonPressed(&button1)){
					status = MODIFY;
					setTimer1(500);
					currentTime = ledTime[RED];
						}
		break;
	case AUTO_GREEN:
		HAL_GPIO_WritePin(GPIOA, LED_RED_Pin|LED_YELLOW_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED_GREEN_Pin, GPIO_PIN_RESET);
		//Display();
		if(timer1_flag ==1){
			status = AUTO_YELLOW;
			currentLedTime = ledTime[YELLOW];
			setTimer1(ledTime[YELLOW]*1000);
		}
		if(timer2_flag ==1){

						currentLedTime--;
						NumberDivision(currentLedTime);
						setTimer2(1000);
				}
		if(isButtonPressed(&button1)){
			status = MODIFY;
			setTimer1(500);
			currentTime = ledTime[RED];
				}
		break;
	default:
		if(isSetClear ==1){
		HAL_GPIO_WritePin(GPIOA, LED_RED_Pin|LED_YELLOW_Pin|LED_GREEN_Pin|LED_GREENB_Pin|LED_REDB_Pin|LED_YELLOWB_Pin, GPIO_PIN_SET);
		isSetClear =0;
		}
		break;
	}

}



