#include "stm32f10x.h"


/************************************************
 ALIENTEK 战舰STM32F103开发板实验0
 工程模板
 注意，这是手册中的新建工程章节使用的main文件 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

#include "digital.h"
#include "Systick.h"

u8 digital_table[]={0xc0,0xf9,0xA4,0xB0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};//0-F 共阳

int main(void)
 {	
   u8 i = 0;
   Systick_Init(72); 
   DIGITAL_Init();
    while(1){
      while(i<=15)
      {
        GPIO_Write(DIGITAL_PORT,digital_table[i]);//对16位进行操作,共阴~digital[i]
        delay_ms(500);
        i++;  
      }
      i = 0;
    };  
 }
