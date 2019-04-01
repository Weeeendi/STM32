#include "Systick.h"
#include "stm32f10x.h"
static u8 fac_us;
static u32 fac_ms;

void Systick_Init(u8 SYSCLK)
{
 
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//sysclk/8 9M
  fac_us=SYSCLK/8;
  fac_ms=(u16)fac_us*1000;
  
}

void delay_us(u32 nus)
{
  u32 temp;
  SysTick->LOAD=nus*fac_us;   //time load
  SysTick->VAL=0x00;  //chear countflag
  SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
  do
  {
    temp=SysTick->CTRL;
  }while((temp&0x01)&&!(temp&(1<<16)));//temp&0x01 is 1 while ENABLE as 1
                                       //temp&(1<<16) is 1 when counter arrived full
  SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; //close counter
  SysTick->VAL=0x00;//chear
}

void delay_ms(u16 nms)
{
  u32 temp;
  SysTick->LOAD=(u32)nms*fac_ms;   //time load
  SysTick->VAL=0x00;  //chear countflag
  SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;//start counter
  do
  {
    temp=SysTick->CTRL;
  }while((temp&0x01)&&!(temp&(1<<16)));//temp&0x01 is 1 while ENABLE as 1
                                       //temp&(1<<16) is 1 when counter arrived full
  SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; //close counter
  SysTick->VAL=0x00;//chear
}
