#include "stm32f10x.h"
#include "led.h"
#include "tftlcd.h"
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

#include "Systick.h"


void LCD_Display(void){
  
  FRONT_COLOR=BLUE;
  LCD_ShowString(0,0*20,tftlcd_data.width,tftlcd_data.height,16," CAN Example");
	LCD_ShowString(0,1*20,tftlcd_data.width,tftlcd_data.height,16,"Tx data:    ");
	LCD_ShowString(0,2*20,tftlcd_data.width,tftlcd_data.height,16,"            ");
  LCD_ShowString(0,3*20,tftlcd_data.width,tftlcd_data.height,16,"Rx data:    ");
  LCD_ShowString(0,4*20,tftlcd_data.width,tftlcd_data.height,16,"            ");
	LCD_ShowString(0,5*20,tftlcd_data.width,tftlcd_data.height,16,"            ");
  LCD_ShowString(0,6*20,tftlcd_data.width,tftlcd_data.height,16,"Author:Wen Di");
}




int main(void)
 {
   SystemInit();
   TFTLCD_Init();
   LCD_Display();
 }
