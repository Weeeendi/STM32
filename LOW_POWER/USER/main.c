#include "usart.h"
#include "system.h"
#include "tftlcd.h"
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

 int main(void)
 {		  
  Systick_Init(72);
  uart1_init(115200);
  TFTLCD_Init();
  kai_display();
}
