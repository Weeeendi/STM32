#include "led.h"

#include "stm32f10x.h"
void LED_Init(void){
  RCC->APB2ENR|=1<<4;
  RCC->APB2ENR|=1<<6;
    
  GPIOC->CRL&=0xFFFFFFF0;
  GPIOC->CRL|=0x00000003;
  GPIOC->ODR|=1;
  
  
//  //GPIOE.5
//  //50MHZ,ÍÆÍìÊä³ö
//  GPIOE->CRL&=0xFF0FFFFF;
//  GPIOE->CRL|=0x00300000;
//  GPIOE->ODR|=1<<5;
}
