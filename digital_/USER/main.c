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

#include "digital.h"
#include "Systick.h"

u8 digital_table[]={0xc0,0xf9,0xA4,0xB0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};//0-F ����

int main(void)
 {	
   u8 i = 0;
   Systick_Init(72); 
   DIGITAL_Init();
    while(1){
      while(i<=15)
      {
        GPIO_Write(DIGITAL_PORT,digital_table[i]);//��16λ���в���,����~digital[i]
        delay_ms(500);
        i++;  
      }
      i = 0;
    };  
 }
