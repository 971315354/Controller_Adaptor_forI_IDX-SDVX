#ifndef __HID_REPORT_H
#define __HID_REPORT_H

#include "usbd_customhid.h"
#include "main.h"

typedef struct {
    uint16_t buttons;  // 10 buttons + 6 padding bits
    int8_t x;          // Encoder 1
    int8_t y;          // Encoder 2
} HID_Report_t;

// 全局 HID 报告结构体
extern HID_Report_t g_hidReport;

// USB 设备句柄（来自 usbd_customhid_if.c）
extern USBD_HandleTypeDef hUsbDeviceFS;

#endif

