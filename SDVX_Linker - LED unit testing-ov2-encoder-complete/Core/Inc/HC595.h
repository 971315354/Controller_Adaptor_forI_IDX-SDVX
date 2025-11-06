#ifndef __HC595_H
#define __HC595_H

#include "stm32f1xx_hal.h"  // 根据你的芯片替换为对应系列，如 stm32f4xx_hal.h


// ===== 函数声明 =====

// 读取 10 个按钮状态（按下为 1）
uint16_t Read_Keys(void);

// 根据按键状态更新 74HC595 输出
void HC595_Update(uint16_t keys);

// 向两个 74HC595 发送 16 位数据（高 8 位→第二个，低 8 位→第一个）
void HC595_Send(uint16_t data);

void HC595_Init(void);

#endif /* __HC595_H */

