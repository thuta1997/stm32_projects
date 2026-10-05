/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define m7F_Pin GPIO_PIN_0
#define m7F_GPIO_Port GPIOC
#define m7R_Pin GPIO_PIN_1
#define m7R_GPIO_Port GPIOC
#define m6R_Pin GPIO_PIN_2
#define m6R_GPIO_Port GPIOC
#define m6F_Pin GPIO_PIN_3
#define m6F_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define door1PWM_Pin GPIO_PIN_6
#define door1PWM_GPIO_Port GPIOA
#define door2PWM_Pin GPIO_PIN_7
#define door2PWM_GPIO_Port GPIOA
#define m2F_Pin GPIO_PIN_5
#define m2F_GPIO_Port GPIOC
#define door3PWM_Pin GPIO_PIN_0
#define door3PWM_GPIO_Port GPIOB
#define door4PWM_Pin GPIO_PIN_1
#define door4PWM_GPIO_Port GPIOB
#define m4F_Pin GPIO_PIN_2
#define m4F_GPIO_Port GPIOB
#define Done_signal_Pin GPIO_PIN_10
#define Done_signal_GPIO_Port GPIOB
#define Done_signal_EXTI_IRQn EXTI15_10_IRQn
#define m3R_Pin GPIO_PIN_12
#define m3R_GPIO_Port GPIOB
#define m5R_Pin GPIO_PIN_13
#define m5R_GPIO_Port GPIOB
#define m5F_Pin GPIO_PIN_14
#define m5F_GPIO_Port GPIOB
#define m4R_Pin GPIO_PIN_15
#define m4R_GPIO_Port GPIOB
#define m1R_Pin GPIO_PIN_6
#define m1R_GPIO_Port GPIOC
#define m1F_Pin GPIO_PIN_8
#define m1F_GPIO_Port GPIOC
#define m8F_Pin GPIO_PIN_9
#define m8F_GPIO_Port GPIOC
#define event_signal_Pin GPIO_PIN_8
#define event_signal_GPIO_Port GPIOA
#define Tx_MCU_Pin GPIO_PIN_9
#define Tx_MCU_GPIO_Port GPIOA
#define Rx_MCU_Pin GPIO_PIN_10
#define Rx_MCU_GPIO_Port GPIOA
#define m3F_Pin GPIO_PIN_11
#define m3F_GPIO_Port GPIOA
#define m2R_Pin GPIO_PIN_12
#define m2R_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define sensor1_Pin GPIO_PIN_10
#define sensor1_GPIO_Port GPIOC
#define sensor2_Pin GPIO_PIN_11
#define sensor2_GPIO_Port GPIOC
#define sensor3_Pin GPIO_PIN_12
#define sensor3_GPIO_Port GPIOC
#define sensor4_Pin GPIO_PIN_2
#define sensor4_GPIO_Port GPIOD
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define m8R_Pin GPIO_PIN_8
#define m8R_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
