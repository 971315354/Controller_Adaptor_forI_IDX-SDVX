#include "encoder.h"
#include "tim.h"
#include "hid_report.h"

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

static int16_t lastCountX = 0;
static int16_t lastCountY = 0;

/* 虚拟摇杆绝对坐标，范围 [-127, 127] */
static int16_t posX = 0;
static int16_t posY = 0;

static float accX = 0.0f;   // 累积余量
static float accY = 0.0f;

static int8_t lastDirX = 0;     // 上一次方向（1正，-1负，0无）
static int8_t lastDirY = 0;

/* 每转一格的步进因子，可根据P/R调整 */
#define ENCODER_STEP_DIV 16   // 每4个脉冲算1步，可自行调节灵敏度
#define IDLE_TIMEOUT_MS    100 // 停止旋转超过此时间自动回中（毫秒）
#define MAX_DIFF_PER_STEP  8    // 每次最大增量

/* 上次有移动的时间戳 */
static uint32_t lastMoveTick = 0;

void Encoder_Init(void)
{
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);

    lastCountX = __HAL_TIM_GET_COUNTER(&htim3);
    lastCountY = __HAL_TIM_GET_COUNTER(&htim4);

    posX = 0;
    posY = 0;
    lastMoveTick = HAL_GetTick();  // 记录初始化时的时间戳
}

void Encoder_Update(void)
{
    int16_t curX = __HAL_TIM_GET_COUNTER(&htim3);
    int16_t curY = __HAL_TIM_GET_COUNTER(&htim4);

    int16_t diffX = curX - lastCountX;
    int16_t diffY = curY - lastCountY;
    lastCountX = curX;
    lastCountY = curY;

    // 处理16位溢出
    if (diffX > 32767) diffX -= 65536;
    else if (diffX < -32768) diffX += 65536;
    if (diffY > 32767) diffY -= 65536;
    else if (diffY < -32768) diffY += 65536;

    // --- 方向检测：判断是否反向 ---
    int8_t dirX = (diffX > 0) ? 1 : (diffX < 0 ? -1 : 0);
    int8_t dirY = (diffY > 0) ? 1 : (diffY < 0 ? -1 : 0);

    if (dirX != 0 && dirX != lastDirX)
    {
        accX = 0;  // 清除积累，让方向反转立即生效
        lastDirX = dirX;
    }
    if (dirY != 0 && dirY != lastDirY)
    {
        accY = 0;
        lastDirY = dirY;
    }

    // --- 累积脉冲，用于慢速补偿 ---
    accX += (float)diffX / ENCODER_STEP_DIV;
    accY += (float)diffY / ENCODER_STEP_DIV;

    int16_t stepX = (int16_t)accX;
    int16_t stepY = (int16_t)accY;
    accX -= stepX;
    accY -= stepY;

    // 限制变化速度
    if (stepX > MAX_DIFF_PER_STEP) stepX = MAX_DIFF_PER_STEP;
    if (stepX < -MAX_DIFF_PER_STEP) stepX = -MAX_DIFF_PER_STEP;
    if (stepY > MAX_DIFF_PER_STEP) stepY = MAX_DIFF_PER_STEP;
    if (stepY < -MAX_DIFF_PER_STEP) stepY = -MAX_DIFF_PER_STEP;

    if (stepX != 0 || stepY != 0)
    {
        posX += stepX;
        posY += stepY;

        // 钳制 [-127, 127]
        if (posX > 127) posX = 127;
        else if (posX < -127) posX = -127;
        if (posY > 127) posY = 127;
        else if (posY < -127) posY = -127;

        lastMoveTick = HAL_GetTick();
    }
    else
    {
        // 长时间无动作 -> 回中
        if (HAL_GetTick() - lastMoveTick > IDLE_TIMEOUT_MS)
        {
            if (posX != 0 || posY != 0)
            {
                posX = 0;
                posY = 0;
                lastMoveTick = HAL_GetTick();
            }
        }
    }

    // --- 仅在数值变化时发送 HID ---
    static int8_t lastSentX = 0;
    static int8_t lastSentY = 0;
    if (posX != lastSentX || posY != lastSentY)
    {
        g_hidReport.x = (int8_t)posX;
        g_hidReport.y = (int8_t)posY;
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&g_hidReport, sizeof(g_hidReport));
        lastSentX = posX;
        lastSentY = posY;
    }
}
