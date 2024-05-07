/*
 * global.h
 *
 *  Created on: May 6, 2024
 *      Author: Admin
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_
#include "software_timer.h"
#include "button.h"
#include "main.h"
#define INIT 1
#define AUTO_RED 2
#define AUTO_YELLOW 3
#define AUTO_GREEN 4
#define MODIFY 5
#define RED 0
#define YELLOW 1
#define GREEN 2

extern int status;
extern int LED;

extern int ledTime[3];
extern int TimeDisplay;
extern int currentLedTime;
extern int ledDisplayTime[2];
extern uint16_t ledDisplay[];
void SetLedTime(int LED,int time);
#endif /* INC_GLOBAL_H_ */
