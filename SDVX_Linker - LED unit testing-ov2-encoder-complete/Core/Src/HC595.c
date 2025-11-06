#include "HC595.h"
#include "main.h"


// ======== 函数声明 ========
static void HC595_WriteBit(uint8_t value, GPIO_TypeDef *DS_PORT, uint16_t DS_PIN);
static void HC595_Latch(void);

void HC595_Init(void)
{
    HAL_GPIO_WritePin(STCP_PORT, STCP_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SHCP_PORT, SHCP_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DS1_PORT, DS1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DS2_PORT, DS2_PIN, GPIO_PIN_RESET);

    HC595_Send(0x0000); // 所有LED灭
}


// ======== 按键读取函数（按你的输入部分保持不变，可自定义） ========
// 返回 10 位按键状态，bit0~bit9 对应按键1~10，按下为 1
uint16_t Read_Keys(void)
{
    uint16_t val = 0;

    // 这里只示例，可根据你的 GPIO 定义调整
    val |= (HAL_GPIO_ReadPin(GPIOA, BT_D_Pin) == GPIO_PIN_RESET) ? (1 << 0) : 0;
    val |= (HAL_GPIO_ReadPin(GPIOA, BT_C_Pin) == GPIO_PIN_RESET) ? (1 << 1) : 0;
    val |= (HAL_GPIO_ReadPin(GPIOA, BT_B_Pin) == GPIO_PIN_RESET) ? (1 << 2) : 0;
    val |= (HAL_GPIO_ReadPin(GPIOA, BT_A_Pin) == GPIO_PIN_RESET) ? (1 << 3) : 0;
    val |= (HAL_GPIO_ReadPin(GPIOA, BT_8) == GPIO_PIN_RESET) ? (1 << 4) : 0;
    val |= (HAL_GPIO_ReadPin(GPIOA, FX_L_Pin) == GPIO_PIN_RESET) ? (1 << 5) : 0;
    val |= (HAL_GPIO_ReadPin(GPIOA, FX_R_Pin) == GPIO_PIN_RESET) ? (1 << 6) : 0;
    val |= (HAL_GPIO_ReadPin(GPIOA, START_Pin) == GPIO_PIN_RESET) ? (1 << 7) : 0;
    val |= (HAL_GPIO_ReadPin(GPIOB, BT_9) == GPIO_PIN_RESET) ? (1 << 8) : 0;
    val |= (HAL_GPIO_ReadPin(GPIOB, BT_10) == GPIO_PIN_RESET) ? (1 << 9) : 0;

    return val;
}

/**
 * @brief  根据按键状态更新 HC595 输出
 * @param  keys: 10 位按键状态，按下为1
 * @note   Qx 高电平表示该按键按下
 */
void HC595_Update(uint16_t keys)
{
    uint8_t data1 = 0; // 第一个 595 的数据（低 8 位）
    uint8_t data2 = 0; // 第二个 595 的数据（高 8 位）

    // 第一个 595：Q1~Q6 对应 按钮1~6
    for (int i = 0; i < 6; i++)
    {
        if (keys & (1 << i))
            data1 |= (1 << (i + 1)); // 从 bit1 开始，Q1~Q6
    }

    // 第二个 595：Q1~Q4 对应 按钮7~10
    for (int i = 6; i < 10; i++)
    {
        if (keys & (1 << i))
            data2 |= (1 << (i - 6 + 1)); // 按钮7对应Q1
    }

    // 拼接成 16 位，高 8 位 = 第二个595，低 8 位 = 第一个595
    uint16_t data = ((uint16_t)data2 << 8) | data1;

    // 发送数据
    HC595_Send(data);
}

/**
 * @brief  向两个74HC595发送16位数据（高8位→第二个，低8位→第一个）
 */
void HC595_Send(uint16_t data)
{
    // 共16位，从高到低依次移入
    for (int i = 15; i >= 0; i--)
    {
        uint8_t bitVal = (data >> i) & 0x01;

        if (i >= 8)
        {
            // 第二个595的DS
            HC595_WriteBit(bitVal, DS2_PORT, DS2_PIN);
        }
        else
        {
            // 第一个595的DS
            HC595_WriteBit(bitVal, DS1_PORT, DS1_PIN);
        }

        // 时钟上升沿
        HAL_GPIO_WritePin(SHCP_PORT, SHCP_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SHCP_PORT, SHCP_PIN, GPIO_PIN_RESET);
    }

    // 锁存输出
    HC595_Latch();
}

/**
 * @brief  写一个bit到指定595的DS引脚
 */
static void HC595_WriteBit(uint8_t value, GPIO_TypeDef *DS_PORT, uint16_t DS_PIN)
{
    HAL_GPIO_WritePin(DS_PORT, DS_PIN, value ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

/**
 * @brief  锁存信号
 */
static void HC595_Latch(void)
{
    HAL_GPIO_WritePin(STCP_PORT, STCP_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(STCP_PORT, STCP_PIN, GPIO_PIN_RESET);
}
