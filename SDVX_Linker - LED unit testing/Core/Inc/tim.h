#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"   
#include "stm32f1xx_hal_gpio.h"  
	
/* 全局句柄声明 */
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

/* 初始化函数声明 */
void MX_TIM3_Init(void);
void MX_TIM4_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */
