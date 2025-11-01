#include "encoder.h"
#include "hid_report.h"

#define DEBOUNCE_MS 2
#define WINDOW_SIZE 2  // 滑动窗口大小

// 用于存储历史状态，去除噪声
static uint8_t enc1_history[WINDOW_SIZE] = {0};
static uint8_t enc2_history[WINDOW_SIZE] = {0};

// 当前窗口的位置索引
static uint8_t enc1_index = 0;
static uint8_t enc2_index = 0;

static uint8_t enc1_last_state = 0;
static uint8_t enc2_last_state = 0;

static uint32_t last_enc1_time = 0;
static uint32_t last_enc2_time = 0;

// 四态查表：根据上一次状态和当前状态，输出旋转方向
static const int8_t enc_table[4][4] = {
    { 0, -1,  1,  0 },
    { 1,  0,  0, -1 },
    { -1, 0,  0,  1 },
    { 0,  1, -1,  0 }
};

// 更新编码器状态
void Encoder_Update(void)
{
    uint32_t now = HAL_GetTick();

    // 编码器1（X 轴）
    if (now - last_enc1_time >= DEBOUNCE_MS) {
        last_enc1_time = now;

        uint8_t A = HAL_GPIO_ReadPin(ENC1_GPIO_Port, ENC1_A_Pin);
        uint8_t B = HAL_GPIO_ReadPin(ENC1_GPIO_Port, ENC1_B_Pin);
        uint8_t current_state = (A << 1) | B;

        // 滑动窗口更新
        enc1_history[enc1_index] = current_state;
        enc1_index = (enc1_index + 1) % WINDOW_SIZE;

        // 判断窗口中最多的状态（如果多数状态一致，判定为有效）
        uint8_t count[4] = {0};  // 用来计数各个状态出现的次数
        for (int i = 0; i < WINDOW_SIZE; i++) {
            count[enc1_history[i]]++;
        }

        // 选择出现次数最多的状态
        uint8_t majority_state = 0;
        for (int i = 1; i < 4; i++) {
            if (count[i] > count[majority_state]) {
                majority_state = i;
            }
        }

        // 获取方向增量
        int8_t delta = enc_table[enc1_last_state][majority_state];
        enc1_last_state = majority_state;

        if (delta != 0) {
            g_hidReport.x += delta;

            if (g_hidReport.x > 127) g_hidReport.x = 127;
            if (g_hidReport.x < -127) g_hidReport.x = -127;

            USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,
                                       (uint8_t*)&g_hidReport,
                                       sizeof(g_hidReport));
        }
    }

    // 编码器2（Y 轴）
    if (now - last_enc2_time >= DEBOUNCE_MS) {
        last_enc2_time = now;

        uint8_t A = HAL_GPIO_ReadPin(ENC2_GPIO_Port, ENC2_A_Pin);
        uint8_t B = HAL_GPIO_ReadPin(ENC2_GPIO_Port, ENC2_B_Pin);
        uint8_t current_state = (A << 1) | B;

        // 滑动窗口更新
        enc2_history[enc2_index] = current_state;
        enc2_index = (enc2_index + 1) % WINDOW_SIZE;

        // 判断窗口中最多的状态（如果多数状态一致，判定为有效）
        uint8_t count[4] = {0};  // 用来计数各个状态出现的次数
        for (int i = 0; i < WINDOW_SIZE; i++) {
            count[enc2_history[i]]++;
        }

        // 选择出现次数最多的状态
        uint8_t majority_state = 0;
        for (int i = 1; i < 4; i++) {
            if (count[i] > count[majority_state]) {
                majority_state = i;
            }
        }

        // 获取方向增量
        int8_t delta = enc_table[enc2_last_state][majority_state];
        enc2_last_state = majority_state;

        if (delta != 0) {
            g_hidReport.y += delta;

            if (g_hidReport.y > 127) g_hidReport.y = 127;
            if (g_hidReport.y < -127) g_hidReport.y = -127;

            USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,
                                       (uint8_t*)&g_hidReport,
                                       sizeof(g_hidReport));
        }
    }
}
