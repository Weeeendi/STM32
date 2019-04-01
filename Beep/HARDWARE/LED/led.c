#include "led.h"
#include "stm32f10x.h"
void LED_Init(void){
  RCC->APB2ENR|=1<<4;
  
  //GPIOB.0
  
  GPIOB->CRL&=0xFFFFFFF0;
  GPIOB->CRL|=0x00000003;
  GPIOB->ODR|=1;
  
  
  //GPIOB.1
  //50MHZ,ÍÆÍìÊä³ö
   GPIOB->CRL&=0xFFFFFF0F;
  GPIOB->CRL|=0x00000030;
  GPIOB->ODR|=1<<1;
}
