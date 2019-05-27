#include "stm32f10x.h"
#include "led.h"
#include "tftlcd.h"
/************************************************
 ALIENTEK ս��STM32F103������ʵ��0
 ����ģ��
 ע�⣬�����ֲ��е��½������½�ʹ�õ�main�ļ� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
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
