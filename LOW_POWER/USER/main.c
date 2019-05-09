#include "led.h"
#include "key.h"
#include "system.h"
#include "tftlcd.h"
#include "usart.h"
#include "SysTick.h" 
/************************************************
 ALIENTEKս��STM32������ʵ��3
 ��������ʵ��  
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


void kai_display()  //������ʾ
{
	FRONT_COLOR=RED;
	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,16,"Touch Test");
	LCD_ShowString(10,30,tftlcd_data.width,tftlcd_data.height,16,"www.prechin.net");
	LCD_ShowString(10,50,tftlcd_data.width,tftlcd_data.height,16,"K_UP:Adjust");	
}

void Enter_Standby_Mode(void)
{     
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);//ʹ��PWR����ʱ��
      PWR_ClearFlag(PWR_FLAG_WU);//���Wake-up ��־
      PWR_WakeUpPinCmd(ENABLE);//ʹ�ܻ��ѹܽ�	ʹ�ܻ���ʧ�ܻ��ѹܽŹ���
      PWR_EnterSTANDBYMode();//�������ģʽ
    } 

void Sys_Enter_Standby(void)
{			 
	RCC_APB2PeriphResetCmd(0X01FC,DISABLE);	//��λ����IO��
	Enter_Standby_Mode();
}

 int main(void)
 {		  
 	LED_Init();			     //LED�˿ڳ�ʼ��
  SysTick_Init(72);
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����NVICΪ2:2
  uart_init(115200);
	KEY_Init();          //��ʼ���밴�����ӵ�Ӳ���ӿ�
  TFTLCD_Init();
	LED0=0;					//�ȵ������
  kai_display();
	while(1)
	{    
    if(KEY_Scan(0)==KEY1_PRES)
    Sys_Enter_Standby();
    delay_ms(10);
	}	 
}

