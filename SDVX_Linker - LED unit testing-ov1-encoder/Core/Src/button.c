#include "button.h"
#include "hid_report.h"

#define DEBOUNCE_COUNT 3  // 去抖次数

static Button_t buttons[BUTTON_COUNT] = {
    {GPIOA, BT_A_Pin, 1, 1, 0},  // BT-A
    {GPIOA, BT_B_Pin, 1, 1, 0},  // BT-B
    {GPIOA, BT_C_Pin, 1, 1, 0},  // BT-C
    {GPIOA, BT_D_Pin, 1, 1, 0},  // BT-D
    {GPIOA, START_Pin, 1, 1, 0}, // START
    {GPIOA, FX_R_Pin, 1, 1, 0},  // FX-R 
    {GPIOA, FX_L_Pin, 1, 1, 0},  // FX-L
    {GPIOA, BT_8, 1, 1, 0},      // BT-8
    {GPIOB, BT_9, 1, 1, 0},      // BT-9
    {GPIOB, BT_10, 1, 1, 0},     // BT-10
};

void Button_Init(void)
{
    for (int i = 0; i < BUTTON_COUNT; i++) {
        buttons[i].state = 1;
        buttons[i].lastState = 1;
        buttons[i].counter = 0; 
    }
}

void Button_Scan(void)
{
    uint8_t changed = 0;

    for (int i = 0; i < BUTTON_COUNT; i++) {
        uint8_t read = HAL_GPIO_ReadPin(buttons[i].port, buttons[i].pin);

        if (read != buttons[i].lastState) {
            buttons[i].counter++;
            if (buttons[i].counter >= DEBOUNCE_COUNT) {
                buttons[i].lastState = read;
                buttons[i].state = read;
                buttons[i].counter = 0;
                changed = 1;

                // 更新 HID 报告按钮位
                if (read == GPIO_PIN_RESET)
                    g_hidReport.buttons |= (1 << i);
                else
                    g_hidReport.buttons &= ~(1 << i);
            }
        } else {
            buttons[i].counter = 0;
        }
    }

    // 如果有按键变化，则发送 HID 报告
    if (changed) {
        USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,
                                   (uint8_t*)&g_hidReport,
                                   sizeof(g_hidReport));
    }
}
