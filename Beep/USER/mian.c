#include "stm32f10x.h"
#include "beep.h"
#include "delay.h"
int main(void)
{
  Beep_Init();
  delay_init(72);
  
  while(1)
  {
    GPIOB->ODR|=1<<5;
    delay_ms(500);
    
    GPIOB->ODR&=~(1<<5);//00100000->11011111
    delay_ms(500);
   }  
}
