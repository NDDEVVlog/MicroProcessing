/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_TIM2_Init(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int  Ex4Counter = 100;
void Exercise4();
void updateClockBuffer();
void SevenSegmentBCD(int number);
void update7SEG ( int index );
int index_led = 0;
int hour = 15 , minute = 8 , second = 50;

const int MAX_LED_MATRIX = 8 ;
int index_led_matrix = 0;
uint8_t matrix_buffer[8] = { 0x01 , 0x02 , 0x03 , 0x04 , 0x05 , 0x06, 0x07 , 0x08};

void setCol(uint8_t val){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, (val >> 7)&0x01);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, (val >> 6)&0x01);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, (val >> 5)&0x01);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, (val >> 4)&0x01);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, (val >> 3)&0x01);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, (val >> 2)&0x01);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, (val >> 1)&0x01);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, (val >> 0)&0x01);
}
void setMATRIX(void){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
}

void updateLEDMatrix(int index){
	setMATRIX();
	setCol(matrix_buffer[index]);
	switch(index){

		case 0 :
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
					break;
		case 1 :
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
					break;
		case 2 :
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
					break;
		case 3 :
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
					break;
		case 4 :
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
					break;
		case 5 :
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
					break;
		case 6 :
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
					break;
		case 7 :
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
					break;
	}
}


int timer0_counter = 0;
int timer0_flag= 0 ;
int timer1_counter = 0;
int timer1_flag= 0 ;
int timer2_counter = 0;
int timer2_flag= 0 ;
int TIMER_CYCLE = 10;

void setTimer0(int duration){
	timer0_counter = duration / TIMER_CYCLE;
	timer0_flag = 0;
}
void setTimer1(int duration){
	timer1_counter = duration / TIMER_CYCLE;
	timer1_flag = 0;
}
void setTimer2(int duration){
	timer2_counter = duration / TIMER_CYCLE;
	timer2_flag = 0;
}
void timer_run(){
	if(timer0_counter >0){
		timer0_counter--;
		if(timer0_counter ==0) timer0_flag=1;
	}
	if(timer1_counter >0){
			timer1_counter--;
			if(timer1_counter ==0) timer1_flag=1;
		}
	if(timer2_counter >0){
			timer2_counter--;
			if(timer2_counter ==0) timer2_flag=1;
		}
}

// Đoạn code này hay quá nên em chép ở đây
void display7SEG(int num) {
  char segNumber[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

  for (int i = 0; i < 7; ++i) {
    // Line needing adjustment for your specific hardware
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 << i, (segNumber[num] >> i) & 1);
  }
}



void Ex5(){

		second ++;
		if ( second >= 60) {
			second = 0;
			minute ++;
		}
		if( minute >= 60) {
			minute = 0;
			hour ++;
		}
		if( hour >=24) {
			hour = 0;
		}
	updateClockBuffer () ;
	HAL_Delay (1000) ;

}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_TIM2_Init();
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  setTimer0(1000);
    setTimer1(1000);
    setTimer2(1000);
    while (1)
    {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    	if(timer2_flag == 1 ){
    	    	  		  update7SEG(index_led);
    	    	  		  index_led++;
    	    	  		  if(index_led >=4) index_led = 0;

    	    	  		  updateLEDMatrix(index_led_matrix);
    	    	  		setTimer2(1000);

    	    	  	  }
    }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, PA4_Pin|PA5_Pin|PA6_Pin|PA7_Pin
                          |PA8_Pin|PA9_Pin|PA11_Pin|PA12_Pin
                          |PA13_Pin|PA15_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, PB0_Pin|PB1_Pin|PB2_Pin|PB10_Pin
                          |PB11_Pin|PB12_Pin|PB3_Pin|PB4_Pin
                          |PB5_Pin|PB6_Pin|PB8_Pin|PB9_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA2_Pin PA3_Pin PA10_Pin PA14_Pin */
  GPIO_InitStruct.Pin = PA2_Pin|PA3_Pin|PA10_Pin|PA14_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4_Pin PA5_Pin PA6_Pin PA7_Pin
                           PA8_Pin PA9_Pin PA11_Pin PA12_Pin
                           PA13_Pin PA15_Pin */
  GPIO_InitStruct.Pin = PA4_Pin|PA5_Pin|PA6_Pin|PA7_Pin
                          |PA8_Pin|PA9_Pin|PA11_Pin|PA12_Pin
                          |PA13_Pin|PA15_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0_Pin PB1_Pin PB2_Pin PB10_Pin
                           PB11_Pin PB12_Pin PB3_Pin PB4_Pin
                           PB5_Pin PB6_Pin PB8_Pin PB9_Pin */
  GPIO_InitStruct.Pin = PB0_Pin|PB1_Pin|PB2_Pin|PB10_Pin
                          |PB11_Pin|PB12_Pin|PB3_Pin|PB4_Pin
                          |PB5_Pin|PB6_Pin|PB8_Pin|PB9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB13_Pin PB14_Pin PB15_Pin */
  GPIO_InitStruct.Pin = PB13_Pin|PB14_Pin|PB15_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
int counter = 50;
int halfTimeCounter =0;
uint8_t numberPA = 6;

const int MAX_LED = 4;

int led_buffer[4] = {1,2,3,4};
int status = 0;
int buffer[4] = {1,2,3,0};

/* */


void Exercise1(){
	counter--;
		if(counter <=0){
		counter = 50;
		if(numberPA == 6){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET );
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET );
		SevenSegmentBCD(1);
		numberPA = 7 ;
		}
		else if ( numberPA == 7)
		{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET );
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET );
		SevenSegmentBCD(2);
		numberPA = 6 ;
		}
		}
}
void SevenSegmentBCD(int number){
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

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, segment_a ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, segment_b ? GPIO_PIN_RESET : GPIO_PIN_SET); // Note the inversion with '!' removed
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, segment_c ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, segment_d ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, segment_e ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, segment_f ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, segment_g ? GPIO_PIN_RESET : GPIO_PIN_SET);


}

void update7SEG ( int index ) {
 switch ( index ) {
 	 case 0:
 		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
 		SevenSegmentBCD( led_buffer[0]);
 		 	 // Display the first 7 SEG with led_buffer [0]
 		 break ;
 	 case 1:
 		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
 		SevenSegmentBCD( led_buffer[0]);
 		 break ;
 	 case 2:
 		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
 		SevenSegmentBCD( led_buffer[0]);
 		 break ;
 	 case 3:
 		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
 		SevenSegmentBCD( led_buffer[0]);
 		 break ;
 	 default :
 		 break ;
 }
 }
void Exercise2(){

	counter--;
			if(counter <=0){
			counter = 50;
			halfTimeCounter++;
			if(halfTimeCounter > 2){
				HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
				HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
				halfTimeCounter = 0;
			}

			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 , GPIO_PIN_SET); // clear all Led
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6 << status, GPIO_PIN_RESET);
			SevenSegmentBCD(buffer[status]);
			status++;
			if(status >=4) status = 0;
			}
}



void Exercise4(){
	Ex4Counter--;
	if(Ex4Counter <= 0){
		if(Ex4Counter % 25 ==0){
			update7SEG(index_led);
						SevenSegmentBCD(buffer[index_led]);
						index_led++;
						if(index_led >=4) index_led = 0;
		}



		Ex4Counter=100;
	}
}


void Exercise7(){

			second ++;
			if ( second >= 60) {
				second = 0;
				minute ++;
			}
			if( minute >= 60) {
				minute = 0;
				hour ++;
			}
			if( hour >=24) {
				hour = 0;
			}
		updateClockBuffer () ;


}


void updateClockBuffer(){
	led_buffer[0] = hour / 10;
	led_buffer[1] = hour % 10;
	led_buffer[2] = minute / 10;
	led_buffer[3] = minute % 10;
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim ){
	//timer_run();
	Exercise2();
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
