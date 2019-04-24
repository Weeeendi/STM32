#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "beep.h"
 
/************************************************
 ALIENTEKս��STM32������ʵ��3
 ��������ʵ��  
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


 int main(void)
 {
  u32 i=0;
 	vu8 key=0;	
	delay_init();	    	 //��ʱ������ʼ��	  
 	LED_Init();			     //LED�˿ڳ�ʼ��
	KEY_Init();          //��ʼ���밴�����ӵ�Ӳ���ӿ�
  LED0=0;
	//GPIOC->BSRR=0xFFFFFFFF;
	while(1)
	{
 		key=KEY_Scan(0);	//�õ���ֵ(1֧��������;0��֧��������)
	  if(key)
		{		
      GPIOC->BSRR=(1<<(i)); //������һλ     
			switch(key)
			{				 
				case KEY0_PRES:	//����left
          if(i==7)i=0;
          else i++;					
					break;
				case KEY2_PRES:	//����right
          if(i==0)i=7;
          else i--;					
					break;
			}
      GPIOC->BSRR=(1<<(16+i));//��λ��1
      
		}else delay_ms(10); 
	}	 
}

