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
#include "stm32f1xx_hal.h"

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
#define BT_A_Pin GPIO_PIN_1
#define BT_A_GPIO_Port GPIOA
#define BT_B_Pin GPIO_PIN_3
#define BT_B_GPIO_Port GPIOA
#define BT_C_Pin GPIO_PIN_5
#define BT_C_GPIO_Port GPIOA
#define BT_D_Pin GPIO_PIN_7
#define BT_D_GPIO_Port GPIOA
#define START_Pin GPIO_PIN_1
#define START_GPIO_Port GPIOB
#define USB_EN_Pin GPIO_PIN_12
#define USB_EN_GPIO_Port GPIOB
#define FX_L_Pin GPIO_PIN_9
#define FX_L_GPIO_Port GPIOA
#define FX_R_Pin GPIO_PIN_4
#define FX_R_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
