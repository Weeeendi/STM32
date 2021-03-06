#include "stm32f10x.h"
#include "led.h"

void LED_Init()
{
    GPIO_InitTypeDef GPIO_InitLed;
    RCC_APB2PeriphClockCmd(LED_PORT_RCC,ENABLE);
  
  
    GPIO_InitLed.GPIO_Pin = LED_PIN;
    GPIO_InitLed.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitLed.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_PORT,&GPIO_InitLed);

    GPIO_SetBits(LED_PORT,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
}
