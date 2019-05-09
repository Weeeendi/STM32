#ifndef __DIGITAL_H
#define __DIGITAL_H
#include "sys.h"

#define DIGITAL_PORT_RCC  RCC_APB2Periph_GPIOC
#define DIGITAL_PIN  (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7)
#define DIGITAL_PORT GPIOC
void DIGITAL_Init(void);

#endif
