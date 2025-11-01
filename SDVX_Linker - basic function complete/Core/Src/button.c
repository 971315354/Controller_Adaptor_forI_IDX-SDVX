#include "button.h"

extern USBD_HandleTypeDef hUsbDeviceFS;  // USB HID 句柄

static Button_t buttons[BUTTON_COUNT] = {
    {GPIOA, GPIO_PIN_1, 1, 1, 0},  // BT-A
    {GPIOA, GPIO_PIN_3, 1, 1, 0},  // BT-B
    {GPIOA, GPIO_PIN_5, 1, 1, 0},  // BT-C
    {GPIOA, GPIO_PIN_7, 1, 1, 0},  // BT-D
    {GPIOA, GPIO_PIN_9, 1, 1, 0}, // FX-L
    {GPIOB, GPIO_PIN_4, 1, 1, 0}, // FX-R
    {GPIOB, GPIO_PIN_1, 1, 1, 0},  // START
};

// HID 报告缓冲区
static uint8_t hidReport[REPORT_SIZE] = {0};

// 定义全局标志位
uint8_t LED_Flag = 0;  

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

void LED_MOD(GPIO_TypeDef *KEY_Port, uint16_t KEY_Pin)
{
    static GPIO_PinState lastState = GPIO_PIN_SET;  // 上次按键状态
    GPIO_PinState nowState = HAL_GPIO_ReadPin(KEY_Port, KEY_Pin);  // 当前按键状态

    // 检测按下沿（从高电平变到低电平）
    if (lastState == GPIO_PIN_SET && nowState == GPIO_PIN_RESET)
    {
        LED_Flag = (LED_Flag + 1) % 3;  // 每次按下按钮，LED_Flag 依次从 0 -> 1 -> 2
        HAL_Delay(20);                  // 去抖动
    }

    lastState = nowState;  // 更新上次按键状态
}

