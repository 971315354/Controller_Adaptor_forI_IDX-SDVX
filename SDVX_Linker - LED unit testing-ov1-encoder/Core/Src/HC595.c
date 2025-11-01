#include "HC595.h"

// 读取按键状态，返回11位数据
uint16_t Read_Keys(void)
{
    uint16_t val = 0;

    val |= (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET) ? (1 << 1) : 0;
    val |= (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET) ? (1 << 2) : 0;
    val |= (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET) ? (1 << 3) : 0;
    val |= (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET) ? (1 << 4) : 0;
    val |= (HAL_GPIO_ReadPin(GPIOA, FX_L_Pin) == GPIO_PIN_RESET) ? (1 << 5) : 0;
    val |= (HAL_GPIO_ReadPin(GPIOA, FX_R_Pin) == GPIO_PIN_RESET) ? (1 << 6) : 0;
    val |= (HAL_GPIO_ReadPin(GPIOA, START_Pin) == GPIO_PIN_RESET) ? (1 << 7) : 0;
    val |= (HAL_GPIO_ReadPin(GPIOA, BT_8) == GPIO_PIN_RESET) ? (1 << 8) : 0;
    val |= (HAL_GPIO_ReadPin(GPIOB, BT_9) == GPIO_PIN_RESET) ? (1 << 9) : 0;
    val |= (HAL_GPIO_ReadPin(GPIOB, BT_10) == GPIO_PIN_RESET) ? (1 << 10) : 0;

    return val;
}

// 向两个74HC595发送16位数据（高8位→第二个，低8位→第一个）
void HC595_Send(uint16_t data)
{
    for (int i = 15; i >= 0; i--)
    {
        // 发送对应位到DS引脚
        uint8_t bitVal = (data >> i) & 0x01;

        if (i >= 7)
            HC595_WriteBit(bitVal, DS2_PORT, DS2_PIN);  // 第二个595
        else
            HC595_WriteBit(bitVal, DS1_PORT, DS1_PIN);  // 第一个595

        // 产生时钟上升沿
        HAL_GPIO_WritePin(SHCP_PORT, SHCP_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SHCP_PORT, SHCP_PIN, GPIO_PIN_RESET);
    }

    // 锁存输出
    HC595_Latch();
}

// 发送一个bit到对应DS
void HC595_WriteBit(uint8_t value, GPIO_TypeDef *DS_PORT, uint16_t DS_PIN)
{
    if (value)
        HAL_GPIO_WritePin(DS_PORT, DS_PIN, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(DS_PORT, DS_PIN, GPIO_PIN_RESET);
}

// 锁存信号
void HC595_Latch(void)
{
    HAL_GPIO_WritePin(STCP_PORT, STCP_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(STCP_PORT, STCP_PIN, GPIO_PIN_RESET);
}
