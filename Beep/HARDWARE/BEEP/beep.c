#include "beep.h"
#include "stm32f10x.h"

void Beep_Init()
{
  RCC->APB2ENR|=1<<3;//
  
  //GBIOB_PIN5
  GPIOB->CRL&=0xFF0FFFFF;
  GPIOB->CRL|=0x00300000;
  GPIOB->ODR|=1<<5;
  
}
