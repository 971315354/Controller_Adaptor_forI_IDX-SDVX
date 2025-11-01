#include "encoder.h"
#include "hid_report.h"
#include "tim.h"   // 确保在 CubeMX 中生成了 TIM3、TIM4 句柄
#include "usb_device.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"


// 保存上一次计数值
static int16_t last_count_x = 0;
static int16_t last_count_y = 0;

// 定义编码器缩放因子（决定灵敏度）
#define ENCODER_SCALE 4

// 初始化编码器（调用 CubeMX 自动生成的 TIM 初始化函数）
void Encoder_Init(void)
{
    // 启动 TIM3（PB4, PB5）
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1 | TIM_CHANNEL_2);

    // 启动 TIM4（PB6, PB7）
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1 | TIM_CHANNEL_2);

    // 清零计数器
    __HAL_TIM_SET_COUNTER(&htim3, 0);
    __HAL_TIM_SET_COUNTER(&htim4, 0);

    last_count_x = 0;
    last_count_y = 0;
}

// 更新编码器状态（在主循环中周期调用）
void Encoder_Update(void)
{
    int16_t count_x = __HAL_TIM_GET_COUNTER(&htim3);
    int16_t count_y = __HAL_TIM_GET_COUNTER(&htim4);

    int16_t delta_x = count_x - last_count_x;
    int16_t delta_y = count_y - last_count_y;

    // 防止溢出
    if (delta_x > 30000) delta_x -= 65535;
    if (delta_x < -30000) delta_x += 65535;
    if (delta_y > 30000) delta_y -= 65535;
    if (delta_y < -30000) delta_y += 65535;

    last_count_x = count_x;
    last_count_y = count_y;

    // 应用缩放系数
    delta_x /= ENCODER_SCALE;
    delta_y /= ENCODER_SCALE;

    if (delta_x != 0 || delta_y != 0)
    {
        g_hidReport.x += delta_x;
        g_hidReport.y += delta_y;

        // 限幅
        if (g_hidReport.x > 127) g_hidReport.x = 127;
        if (g_hidReport.x < -127) g_hidReport.x = -127;
        if (g_hidReport.y > 127) g_hidReport.y = 127;
        if (g_hidReport.y < -127) g_hidReport.y = -127;

        // 发送 HID 报告
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,
                                   (uint8_t*)&g_hidReport,
                                   sizeof(g_hidReport));
    }
}
