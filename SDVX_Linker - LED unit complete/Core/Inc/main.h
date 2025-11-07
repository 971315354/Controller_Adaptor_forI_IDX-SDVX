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

//按键引脚
#define BT_A_Pin GPIO_PIN_0
#define BT_A_GPIO_Port GPIOA
#define BT_B_Pin GPIO_PIN_1
#define BT_B_GPIO_Port GPIOA
#define BT_C_Pin GPIO_PIN_2
#define BT_C_GPIO_Port GPIOA
#define BT_D_Pin GPIO_PIN_3
#define BT_D_GPIO_Port GPIOA
#define START_Pin GPIO_PIN_4
#define START_GPIO_Port GPIOB
#define USB_EN_Pin GPIO_PIN_12
#define USB_EN_GPIO_Port GPIOB
#define FX_L_Pin GPIO_PIN_6
#define FX_L_GPIO_Port GPIOA
#define FX_R_Pin GPIO_PIN_5
#define FX_R_GPIO_Port GPIOB
#define BT_8 GPIO_PIN_7
#define BT_9 GPIO_PIN_0
#define BT_10 GPIO_PIN_1



//#define BT_A_LED_PIN GPIO_PIN_0
//#define BT_B_LED_PIN GPIO_PIN_2
//#define BT_C_LED_PIN GPIO_PIN_4
//#define BT_D_LED_PIN GPIO_PIN_6
//#define FX_L_LED_PIN GPIO_PIN_8
//#define FX_R_LED_PIN GPIO_PIN_3
//#define START_LED_PIN GPIO_PIN_0
//#define LED_MOD_LED_PIN GPIO_PIN_10

//#define LED_MOD_PIN GPIO_PIN_11


// HC595引脚
#define DS1_PIN     GPIO_PIN_9   // 第一个74HC595的DS引脚
#define DS1_PORT    GPIOB

#define DS2_PIN     GPIO_PIN_8   // 第二个74HC595的DS引脚
#define DS2_PORT    GPIOB

#define SHCP_PIN    GPIO_PIN_9   // 时钟引脚（移位时钟）
#define SHCP_PORT   GPIOA

#define STCP_PIN    GPIO_PIN_8   // 锁存引脚
#define STCP_PORT   GPIOA

// 编码器引脚
#define ENC1_A_Pin GPIO_PIN_4
#define ENC1_B_Pin GPIO_PIN_5
#define ENC1_GPIO_Port GPIOB

#define ENC2_A_Pin GPIO_PIN_6
#define ENC2_B_Pin GPIO_PIN_7
#define ENC2_GPIO_Port GPIOB




/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
