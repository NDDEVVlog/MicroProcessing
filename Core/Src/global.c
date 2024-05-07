/*
 * global.c
 *
 *  Created on: May 6, 2024
 *      Author: Admin
 */
#include "global.h"

int status = 0;
int LED = 0;


int ledTime[3] ={8,3,5};
int currentLedTime;
int TimeDisplay;
int ledDisplayTime[2];
uint16_t ledDisplay[] = {Display10_Pin,Display1_Pin};

void SetLedTime(int LED,int time){
	ledTime[LED] = time;
}
