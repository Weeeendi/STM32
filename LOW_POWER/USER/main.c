#include "led.h"
#include "key.h"
#include "system.h"
#include "tftlcd.h"
#include "usart.h"
#include "SysTick.h" 
/************************************************
 ALIENTEK战舰STM32开发板实验3
 按键输入实验  
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


void kai_display()  //开机显示
{
	FRONT_COLOR=RED;
	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,16,"Touch Test");
	LCD_ShowString(10,30,tftlcd_data.width,tftlcd_data.height,16,"www.prechin.net");
	LCD_ShowString(10,50,tftlcd_data.width,tftlcd_data.height,16,"K_UP:Adjust");	
}

void Enter_Standby_Mode(void)
{     
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);//使能PWR外设时钟
      PWR_ClearFlag(PWR_FLAG_WU);//清除Wake-up 标志
      PWR_WakeUpPinCmd(ENABLE);//使能唤醒管脚	使能或者失能唤醒管脚功能
      PWR_EnterSTANDBYMode();//进入待机模式
    } 

void Sys_Enter_Standby(void)
{			 
	RCC_APB2PeriphResetCmd(0X01FC,DISABLE);	//复位所有IO口
	Enter_Standby_Mode();
}

 int main(void)
 {		  
 	LED_Init();			     //LED端口初始化
  SysTick_Init(72);
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置NVIC为2:2
  uart_init(115200);
	KEY_Init();          //初始化与按键连接的硬件接口
  TFTLCD_Init();
	LED0=0;					//先点亮红灯
  kai_display();
	while(1)
	{    
    if(KEY_Scan(0)==KEY1_PRES)
    Sys_Enter_Standby();
    delay_ms(10);
	}	 
}

