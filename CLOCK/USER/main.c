#include "stm32f10x.h"


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

#include "led.h"
#include "Systick.h"


  
 
 int main(void)
 {	
   Systick_Init(72); 
   LED_Init();
    while(1){
      GPIO_ResetBits(LED_PORT,GPIO_Pin_0);
      GPIO_ResetBits(LED_PORT,GPIO_Pin_7);
      delay_ms(500);
      GPIO_SetBits(LED_PORT,GPIO_Pin_0);
      GPIO_SetBits(LED_PORT,GPIO_Pin_7);
      delay_ms(500);
      
    };  
 }
