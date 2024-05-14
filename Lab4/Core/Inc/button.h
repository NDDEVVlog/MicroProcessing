/*
 * button.h
 *
 *  Created on: Sep 21, 2022
 *      Author: KAI
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"


#define NORMAL_STATE SET
#define PRESSED_STATE RESET

extern int button1_flag;

int isButtonPressed( Button* button);

/*typedef struct {
    GPIO_TypeDef* GPIOx;
    uint16_t GPIO_Pin;
    int KeyReg0;
    int KeyReg1;
    int KeyReg2;
    int KeyReg3;
    int TimeOutForKeyPress;
    int button1_flag;
} Button;*/





#endif /* INC_BUTTON_H_ */
