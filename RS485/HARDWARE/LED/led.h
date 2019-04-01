//ifndef 如果已经定义不再定义
#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"
#define LED_PORT_RCC  RCC_APB2Periph_GPIOC
#define LED_PIN  (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7)
#define LED_PORT GPIOC

void LED_Init(void);


#endif
