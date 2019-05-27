#ifndef __SYSTICK_H
#define __SYSTICK_H
#include "system.h"

void Systick_Init(u8 SYSCLK);
void delay_us(u32 nus);
void delay_ms(u16 nms);

#endif
