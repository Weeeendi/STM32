#include "stm32f10x.h"
#include "led.h"

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
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
  
  USART_Init(USART1,&USART_InitStruct);
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 
  
  //Usart1 NVIC 配置
  NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStruct);	//根据指定的参数初始化VIC寄存器
  
  
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
