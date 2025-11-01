#ifndef __HC595_H
#define __HC595_H

#include "main.h"

void HC595_Send(uint16_t data);
void HC595_WriteBit(uint8_t value, GPIO_TypeDef *DS_PORT, uint16_t DS_PIN);
void HC595_Latch(void);
uint16_t Read_Keys(void);

#endif
