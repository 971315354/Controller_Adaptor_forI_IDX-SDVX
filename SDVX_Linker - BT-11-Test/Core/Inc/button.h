#ifndef __BUTTON_H
#define __BUTTON_H

#include "main.h"
#include "hid_report.h"

#define BUTTON_COUNT 11
#define DEBOUNCE_DELAY 5      // 5ms 扫描间隔

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
    uint8_t state;        // 当前稳定状态
    uint8_t lastState;    // 上次稳定状态
    uint8_t counter;      // 消抖计数器
} Button_t;

void Button_Init(void);
void Button_Scan(void);

#endif
