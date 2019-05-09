#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "beep.h"
 



 int main(void)
 {
  u32 i=0;
 	vu8 key=0;	
	delay_init();	    	 //延时函数初始化	  
 	LED_Init();			     //LED端口初始化
	KEY_Init();          //初始化与按键连接的硬件接口
  LED0=0;
	//GPIOC->BSRR=0xFFFFFFFF;
	while(1)
	{
 		key=KEY_Scan(0);	//得到键值(1支持连续按;0不支持连续按)
	  if(key)
		{		
      GPIOC->BSRR=(1<<(i)); //清零上一位     
			switch(key)
			{				 
				case KEY0_PRES:	//控制left
          if(i==7)i=0;
          else i++;					
					break;
				case KEY2_PRES:	//控制right
          if(i==0)i=7;
          else i--;					
					break;
			}
      GPIOC->BSRR=(1<<(16+i));//该位置1
      
		}else delay_ms(10); 
	}	 
}

