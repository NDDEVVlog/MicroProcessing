/*
 * Dis7SEG.c
 *
 *  Created on: May 7, 2024
 *      Author: Admin
 */

#ifndef SRC_DIS7SEG_C_
#define SRC_DIS7SEG_C_

#include "global.h"

uint8_t switchLED=1;
void NumberDivision(int number){
	//if(number >= 99 || number <= 0 ) return;
	ledDisplayTime[0] = number /10;
	ledDisplayTime[1] = number %10;

}

void display7SEG(int number) {
	uint8_t bit_d = (number & 0x01)>>0;  // Extracting least significant bit (bit 0)
		    uint8_t bit_c = (number & 0x02)>>1 ;  // Extracting bit 1
		    uint8_t bit_b = (number & 0x04) >>2;  // Extracting bit 2
		    uint8_t bit_a = (number & 0x08) >>3;  // Extracting most significant bit (bit 3)


		    uint8_t segment_a = (bit_a || bit_c || (!bit_b && !bit_d) | (bit_b && bit_d)) ? 1 : 0;
		    uint8_t segment_b = (!bit_b || (bit_c && bit_d)|| (!bit_c && !bit_d)) ? 1 : 0 ;
		    uint8_t segment_c = (bit_d || !bit_c || bit_b) ? 1 : 0;
		    uint8_t segment_d = ((!bit_c && bit_b && bit_d) || (bit_c && !bit_d) || (!bit_b && !bit_d) || (!bit_b && bit_c) || bit_a) ? 1  : 0;
		    uint8_t segment_e = ((!bit_b || bit_c) && !bit_d) ? 1 : 0 ;
		    uint8_t segment_f = ((!bit_c && bit_b) || (!bit_c && !bit_d) || (bit_b && !bit_d) || bit_a) ? 1 : 0;
		    uint8_t segment_g = (  bit_a ||  (bit_b && !bit_c) || (!bit_b && bit_c)|| (bit_c && !bit_d)) ? 1: 0;

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, !segment_a ? GPIO_PIN_RESET : GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, !segment_b ? GPIO_PIN_RESET : GPIO_PIN_SET); // Note the inversion with '!' removed
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, !segment_c ? GPIO_PIN_RESET : GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, !segment_d ? GPIO_PIN_RESET : GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, !segment_e ? GPIO_PIN_RESET : GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, !segment_f ? GPIO_PIN_RESET : GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, !segment_g ? GPIO_PIN_RESET : GPIO_PIN_SET);
}
void Display(){

	if(timer3_flag ==1 && switchLED ==1){
	HAL_GPIO_WritePin(GPIOA, ledDisplay[0], GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, ledDisplay[1], GPIO_PIN_SET);
	display7SEG(ledDisplayTime[0]);
	switchLED = 0;
	setTimer3(500);
	}
	if(timer3_flag ==1 && switchLED ==0 ){
	HAL_GPIO_WritePin(GPIOA, ledDisplay[1], GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, ledDisplay[0], GPIO_PIN_SET);
	display7SEG(ledDisplayTime[1]);
	switchLED = 1;
		setTimer3(500);
	}

}

#endif /* SRC_DIS7SEG_C_ */
