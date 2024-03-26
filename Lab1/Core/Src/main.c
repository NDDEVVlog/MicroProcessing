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
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

typedef enum {false,true} bool;
void ToggleLED(void);
void SevenSegmentBCD(int number);
void REDYELLOWGREEN(void);

bool  isToggleLed = true ;

uint16_t timerCount = 5;
uint8_t state = 1;
int tempNum;

struct LED{
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;
};

struct LED Red = {LED_RED_GPIO_Port,LED_RED_Pin};
struct LED Yellow = {LED_YELLOW_GPIO_Port,LED_YELLOW_Pin};
struct LED Green = {LED_GREEN_GPIO_Port,LED_GREEN_Pin};
struct LED RedB = {LED_RED_B_GPIO_Port,LED_RED_B_Pin};
struct LED YellowB = {LED_YELLOW_B_GPIO_Port,LED_YELLOW_B_Pin};
struct LED GreenB = {LED_GREEN_B_GPIO_Port,LED_GREEN_B_Pin};

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
void setNumberOnClock(int num){
 if(num < 0 ) num = 0;
 if(num > 11) num = 11;
 tempNum = num +4 ;
 HAL_GPIO_WritePin(GPIOA,(uint16_t) (1 << tempNum),GPIO_PIN_SET);

}
void clearNumberOnClock ( int num ){
  if(num < 0 ) num = 0;
    if(num > 11) num = 11;
    tempNum = num +4 ;
    HAL_GPIO_WritePin(GPIOA,(uint16_t) (1 <<
tempNum),GPIO_PIN_RESET);
 }
void clearAllClock ( void ) {
 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5 |GPIO_PIN_6 |GPIO_PIN_7 | GPIO_PIN_8|
GPIO_PIN_9 |GPIO_PIN_10 |GPIO_PIN_11 |GPIO_PIN_12 |GPIO_PIN_13 |GPIO_PIN_14 |GPIO_PIN_15 ,
GPIO_PIN_SET);


}
void SevenSegmentBCD(int number){
  uint8_t bit_d = (number & 0x01)>>0;  // Extracting least significant bit (bit0)
     uint8_t bit_c = (number & 0x02)>>1 ;  // Extracting bit 1
     uint8_t bit_b = (number & 0x04) >>2;  // Extracting bit 2
     uint8_t bit_a = (number & 0x08) >>3;  // Extracting most significant bit(bit 3)


     uint8_t segment_a = (bit_a || bit_c || (!bit_b && !bit_d) | (bit_b &&
bit_d)) ? 1 : 0;
     uint8_t segment_b = (!bit_b || (bit_c && bit_d)|| (!bit_c && !bit_d)) ? 1
: 0 ;
     uint8_t segment_c = (bit_d || !bit_c || bit_b) ? 1 : 0;
     uint8_t segment_d = ((!bit_c && bit_b && bit_d) || (bit_c && !bit_d) ||
(!bit_b && !bit_d) || (!bit_b && bit_c) || bit_a) ? 1  : 0;
     uint8_t segment_e = ((!bit_b || bit_c) && !bit_d) ? 1 : 0 ;
     uint8_t segment_f = ((!bit_c && bit_b) || (!bit_c && !bit_d) || (bit_b &&
!bit_d) || bit_a) ? 1 : 0;
     uint8_t segment_g = (  bit_a ||  (bit_b && !bit_c) || (!bit_b && bit_c)||
(bit_c && !bit_d)) ? 1: 0;

 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, !segment_a ? GPIO_PIN_RESET :
GPIO_PIN_SET);
 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, !segment_b ? GPIO_PIN_RESET :
GPIO_PIN_SET); // Note the inversion with '!' removed
 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, !segment_c ? GPIO_PIN_RESET :
GPIO_PIN_SET);
 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, !segment_d ? GPIO_PIN_RESET :
 GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, !segment_e ? GPIO_PIN_RESET :
 GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, !segment_f ? GPIO_PIN_RESET :
 GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, !segment_g ? GPIO_PIN_RESET :
 GPIO_PIN_SET);


 }
 void AdjustLed(struct LED A, struct LED B, struct LED C, struct LED D, struct LED E,
 struct LED F) {
     if (state == 1) {
         if (timerCount <= 2) {
             // State 1, Timer count less than or equal to 2
             HAL_GPIO_WritePin(GPIOA, A.GPIO_Pin | E.GPIO_Pin, GPIO_PIN_RESET);
             HAL_GPIO_WritePin(GPIOA, B.GPIO_Pin | D.GPIO_Pin | F.GPIO_Pin |
 C.GPIO_Pin, GPIO_PIN_SET);

         } else if (timerCount <= 5) {
             // State 1, Timer count between 3 and 5
             // Red LED on, others off
             HAL_GPIO_WritePin(GPIOA, A.GPIO_Pin | F.GPIO_Pin, GPIO_PIN_RESET);
             HAL_GPIO_WritePin(GPIOA, B.GPIO_Pin | D.GPIO_Pin | E.GPIO_Pin |
 C.GPIO_Pin, GPIO_PIN_SET);
         }
     } else if (state == 2) {
         if (timerCount <= 2) {
             // State 2, Timer count less than or equal to 2
             HAL_GPIO_WritePin(GPIOA, D.GPIO_Pin | B.GPIO_Pin, GPIO_PIN_RESET);
             HAL_GPIO_WritePin(GPIOA, E.GPIO_Pin | A.GPIO_Pin | F.GPIO_Pin |
 C.GPIO_Pin, GPIO_PIN_SET);

         } else if (timerCount <= 5) {
             // State 2, Timer count between 3 and 5
             // Red LED on, others off
             HAL_GPIO_WritePin(GPIOA, D.GPIO_Pin | C.GPIO_Pin, GPIO_PIN_RESET);
             HAL_GPIO_WritePin(GPIOA, B.GPIO_Pin | A.GPIO_Pin | E.GPIO_Pin |
 F.GPIO_Pin, GPIO_PIN_SET);
         }
     }
 }
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
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  uint16_t ledpin = 4;
  while (1)
  {
  HAL_GPIO_TogglePin(GPIOA,(uint16_t) (1 << ledpin));
  ledpin+= 1;
  if(ledpin >15) ledpin =4;
  HAL_Delay(1000);
  }

 /* while (1)
    {
     if(timerCount <= 0) {timerCount = 5;
        if(state ==1) state = 2;
        else if(state ==2) state = 1;
     }
     AdjustLed(Red, Yellow, Green, RedB, YellowB, GreenB);
      /* USER CODE END WHILE */

      /* USER CODE BEGIN 3 */
      SevenSegmentBCD(timerCount);

     timerCount--;
      HAL_Delay(1000);
    }*/
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
  HAL_GPIO_WritePin(GPIOA, PA1_Pin|PA2_Pin|PA3_Pin|PA4_Pin
                          |LED_RED_Pin|LED_YELLOW_Pin|LED_GREEN_Pin|LED_RED_B_Pin
                          |LED_YELLOW_B_Pin|LED_GREEN_B_Pin|PA11_Pin|PA12_Pin
                          |PA13_Pin|PA14_Pin|PA15_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, PB0_Pin|PB1_Pin|PB2_Pin|PB3_Pin
                          |PB4_Pin|PB5_Pin|PB6_Pin|PB7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA1_Pin PA2_Pin PA3_Pin PA4_Pin
                           LED_RED_Pin LED_YELLOW_Pin LED_GREEN_Pin LED_RED_B_Pin
                           LED_YELLOW_B_Pin LED_GREEN_B_Pin PA11_Pin PA12_Pin
                           PA13_Pin PA14_Pin PA15_Pin */
  GPIO_InitStruct.Pin = PA1_Pin|PA2_Pin|PA3_Pin|PA4_Pin
                          |LED_RED_Pin|LED_YELLOW_Pin|LED_GREEN_Pin|LED_RED_B_Pin
                          |LED_YELLOW_B_Pin|LED_GREEN_B_Pin|PA11_Pin|PA12_Pin
                          |PA13_Pin|PA14_Pin|PA15_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0_Pin PB1_Pin PB2_Pin PB3_Pin
                           PB4_Pin PB5_Pin PB6_Pin PB7_Pin */
  GPIO_InitStruct.Pin = PB0_Pin|PB1_Pin|PB2_Pin|PB3_Pin
                          |PB4_Pin|PB5_Pin|PB6_Pin|PB7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10_Pin PB11_Pin */
  GPIO_InitStruct.Pin = PB10_Pin|PB11_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */


/*void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim )
{
	counter--;
	if( counter <= 0) {

	flag = 1;
	HAL_GPIO_TogglePin ( LED_RED_GPIO_Port , LED_RED_Pin ) ;
	}
}*/
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
