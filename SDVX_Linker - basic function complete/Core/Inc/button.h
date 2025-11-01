#ifndef __BUTTON_H
#define __BUTTON_H

#include "main.h"
#include "usbd_custom_hid_if.h"

#define BUTTON_COUNT 7
#define DEBOUNCE_DELAY 5      // 5ms 扫描间隔
#define REPORT_SIZE    4      // HID 报告长度（自定义）

extern uint8_t LED_Flag;		//声明全局标志位

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
    uint8_t state;        // 当前稳定状态
    uint8_t lastState;    // 上次稳定状态
    uint8_t counter;      // 消抖计数器
} Button_t;

void Button_Init(void);
void Button_Scan(void);
void LED_MOD(GPIO_TypeDef *KEY_Port, uint16_t KEY_Pin);

#endif
