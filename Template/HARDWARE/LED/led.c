#include "led.h"
#include "stm32f10x.h"

void LED_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruscture;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//GPIOB
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);//GPIOE

  GPIO_InitStruscture.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruscture.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStruscture.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&GPIO_InitStruscture);
  GPIO_Init(GPIOE,&GPIO_InitStruscture);
   
  GPIO_SetBits(GPIOB,GPIO_Pin_5);
  GPIO_SetBits(GPIOE,GPIO_Pin_5);
}
