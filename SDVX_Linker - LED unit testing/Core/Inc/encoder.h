#ifndef __ENCODER_H
#define __ENCODER_H

#include "main.h"
#include "usbd_customhid.h"
#include "tim.h"

// 外部 USB 设备句柄
extern USBD_HandleTypeDef hUsbDeviceFS;

void Encoder_Init(void);
void Encoder_Update(void);

#endif
