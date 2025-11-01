#include "encoder.h"
#include "tim.h"
#include "hid_report.h"

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

static int16_t lastCountX = 0;
static int16_t lastCountY = 0;

/* 虚拟摇杆绝对坐标，范围 [-127, 127] */
static int8_t posX = 0;
static int8_t posY = 0;

/* 每转一格的步进因子，可根据P/R调整 */
#define ENCODER_STEP_DIV 4   // 每4个脉冲算1步，可自行调节灵敏度

void Encoder_Init(void)
{
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);

    lastCountX = __HAL_TIM_GET_COUNTER(&htim3);
    lastCountY = __HAL_TIM_GET_COUNTER(&htim4);

    posX = 0;
    posY = 0;
}

void Encoder_Update(void)
{
    int16_t curX = __HAL_TIM_GET_COUNTER(&htim3);
    int16_t curY = __HAL_TIM_GET_COUNTER(&htim4);

    int16_t diffX = curX - lastCountX;
    int16_t diffY = curY - lastCountY;
    lastCountX = curX;
    lastCountY = curY;

    // 处理计数器溢出（16位定时器）
    if (diffX > 32767) diffX -= 65536;
    else if (diffX < -32768) diffX += 65536;

    if (diffY > 32767) diffY -= 65536;
    else if (diffY < -32768) diffY += 65536;

    // 减少灵敏度（每 ENCODER_STEP_DIV 个脉冲为1步）
    diffX /= ENCODER_STEP_DIV;
    diffY /= ENCODER_STEP_DIV;

    // 累积位置
    posX += diffX;
    posY += diffY;

    // 环绕映射 [-127,127]
    if (posX > 127) posX = -127 + (posX - 128);
    if (posX < -127) posX = 127 + (posX + 128);

    if (posY > 127) posY = -127 + (posY - 128);
    if (posY < -127) posY = 127 + (posY + 128);

    // 写入 HID 报告
    g_hidReport.x = posX;
    g_hidReport.y = posY;

	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,
						   (uint8_t*)&g_hidReport,
						   sizeof(g_hidReport));
}
