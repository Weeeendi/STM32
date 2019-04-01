#include "stm32f10x.h"
#include "delay.h"
typedef unsigned int u32;//类型重定义unsigned int --u32

void SystemInit()//对stm32初始化
{
  
}
/******************************************
*函数名:delay
*函数功能:延时函数,通过while循环占用CPU,达到定时效果
*输出:i
*输出:无
*******************************************/
//void delay(u32 i)
//{
//  while(i--);
//}

int main(void)
{
  RCC->APB2ENR|=1<<4;
  //GPIOC->CRL&=~(0x0F<<(4*0));
  //GPIOC->CRL|=(3<<4*0);
  GPIOC->CRL&=0xFFFFFF00;
  GPIOC->CRL|=0x00000033;
  GPIOC->BSRR=(1<<(16+0));
  GPIOC->BSRR=(1<<(16+1));
  delay_init(72);
  
  while(1){
    GPIOC->BSRR=(1<<(16+0));
    GPIOC->BSRR=(1<<(16+1));
    //delay(0xFFFFF);
    delay_ms(250);
    GPIOC->BSRR=(1<<(0));
    GPIOC->BSRR=(1<<(1));
    //delay(0xFFFFF);
    delay_ms(250);
  }
}
