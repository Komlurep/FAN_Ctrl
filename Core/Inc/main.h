/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SW5_Pin GPIO_PIN_5
#define SW5_GPIO_Port GPIOE
#define SW6_Pin GPIO_PIN_6
#define SW6_GPIO_Port GPIOE
#define FANSW_Pin GPIO_PIN_11
#define FANSW_GPIO_Port GPIOD
#define SER_Pin GPIO_PIN_8
#define SER_GPIO_Port GPIOC
#define DISEN_Pin GPIO_PIN_9
#define DISEN_GPIO_Port GPIOC
#define DISLK_Pin GPIO_PIN_8
#define DISLK_GPIO_Port GPIOA
#define SCK_Pin GPIO_PIN_11
#define SCK_GPIO_Port GPIOA
#define A3_Pin GPIO_PIN_12
#define A3_GPIO_Port GPIOA
#define A0_Pin GPIO_PIN_15
#define A0_GPIO_Port GPIOA
#define A1_Pin GPIO_PIN_10
#define A1_GPIO_Port GPIOC
#define A2_Pin GPIO_PIN_11
#define A2_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
