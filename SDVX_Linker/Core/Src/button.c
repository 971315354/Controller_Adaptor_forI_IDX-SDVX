#include "button.h"

extern USBD_HandleTypeDef hUsbDeviceFS;  // USB HID 句柄

static Button_t buttons[BUTTON_COUNT] = {
    {GPIOA, GPIO_PIN_0, 1, 1, 0},  // BT-A
    {GPIOA, GPIO_PIN_1, 1, 1, 0},  // BT-B
    {GPIOB, GPIO_PIN_0, 1, 1, 0},  // BT-C
    {GPIOB, GPIO_PIN_1, 1, 1, 0},  // BT-D
    {GPIOC, GPIO_PIN_13, 1, 1, 0}, // FX-L
    {GPIOC, GPIO_PIN_14, 1, 1, 0}, // FX-R
    {GPIOA, GPIO_PIN_7, 1, 1, 0},  // START
};

// HID 报告缓冲区
static uint8_t hidReport[REPORT_SIZE] = {0};

void Button_Init(void)
{
    // 按钮初始化已在 MX_GPIO_Init() 完成
    // 这里只是清零状态
    for (int i = 0; i < BUTTON_COUNT; i++) {
        buttons[i].state = 1;       // 默认高电平（未按）
        buttons[i].lastState = 1;
        buttons[i].counter = 0;
    }
}

void Button_Scan(void)
{
    uint8_t changed = 0;

    for (int i = 0; i < BUTTON_COUNT; i++) {
        uint8_t read = HAL_GPIO_ReadPin(buttons[i].port, buttons[i].pin);

        // 消抖处理
        if (read != buttons[i].lastState) {
            buttons[i].counter++;
            if (buttons[i].counter >= 3) {  // 连续3次不同则认为状态稳定
                buttons[i].lastState = read;
                buttons[i].state = read;
                buttons[i].counter = 0;
                changed = 1;
            }
        } else {
            buttons[i].counter = 0;
        }

        // 将状态写入 HID 报告位
        if (buttons[i].state == 0) {  // 按下
            hidReport[0] |= (1 << i);
        } else {                      // 松开
            hidReport[0] &= ~(1 << i);
        }
    }

    if (changed) {
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, hidReport, REPORT_SIZE);
    }
}
