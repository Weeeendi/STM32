#include "stm32f10x.h"
#include "led.h"

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
static u8 digital[] = {0xc0,0xf9,0xA4,0xB0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};
static u8 Number;

void My_USART_Initial(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  USART_InitTypeDef USART_InitStruct;
  NVIC_InitTypeDef NVIC_InitStruct;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE); 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOA,&GPIO_InitStruct);
  
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOA,&GPIO_InitStruct);
  
  USART_InitStruct.USART_BaudRate = 9600;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct.USART_Parity = USART_Parity_No;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
  
  USART_Init(USART1,&USART_InitStruct);
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
  
  //Usart1 NVIC ����
  NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStruct);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
  
}
void USART1_IRQHandler(void)
{
  u8 res;
  if(USART_GetITStatus(USART1, USART_IT_RXNE))
  {
    res = USART_ReceiveData(USART1);//USART->DR
    USART_SendData(USART1,res);
    Number = res;
		GPIO_Write(GPIOC,digital[Number]);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
  }
  USART_ClearFlag(USART1, USART_FLAG_TC);
}


int main(void)
 {
   LED_Init();
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   My_USART_Initial();
   while(1);
 }
