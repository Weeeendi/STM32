#include "stm32f10x.h"
#include "can.h"
#include <string.h>

CanRxMsg CanRxMessage;
CanTxMsg CanTxMessage;

void CAN1_Init(){
  GPIO_InitTypeDef GPIO_InitStruct;
  
  
  
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE); 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
  
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStruct.GPIO_Pin = CAN_TX_Pin;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(CAN_TX_Port,&GPIO_InitStruct);
  
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStruct.GPIO_Pin = CAN_RX_Pin;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(CAN_RX_Port,&GPIO_InitStruct);
  
//  USART_InitStruct.USART_BaudRate = 9600;
//  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//  USART_InitStruct.USART_Parity = USART_Parity_No;
//  USART_InitStruct.USART_StopBits = USART_StopBits_1;
//  USART_InitStruct.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
//  
//  USART_Init(USART1,&USART_InitStruct);
//  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
//  USART_Cmd(USART1, ENABLE);                    //使能串口1 
  
}

void CAN1_MODE_Config(void)
{
  CAN_InitTypeDef CAN_InitStructure;
  CAN_FilterInitTypeDef CAN_FilterInitStructure;
  NVIC_InitTypeDef NVIC_InitStruct;
   
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
  CAN_DeInit(CAN1);
  
  CAN_InitStructure.CAN_ABOM = DISABLE;                     //离线模式由软件实现
  CAN_InitStructure.CAN_AWUM = DISABLE;                     //软件唤醒
  CAN_InitStructure.CAN_TTCM = DISABLE;                     //禁止时间触发通信模式
  CAN_InitStructure.CAN_NART = ENABLE;                      //禁止自动重传
  CAN_InitStructure.CAN_TXFP = DISABLE;                     //优先级由报文的标识符来决定
  CAN_InitStructure.CAN_RFLM = DISABLE;                     //接受溢出时FIFO不锁定，下一个收到的报文覆盖原有报文
  CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack;           //CAN硬件工作环回模式
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;                  //重新同步跳跃宽度为2个时间单位
  CAN_InitStructure.CAN_BS1 = CAN_BS1_8tq;                  //时间段为8个时间单位
  CAN_InitStructure.CAN_BS2 = CAN_BS2_7tq;                  //时间段为7个时间单位
  CAN_InitStructure.CAN_Prescaler = 5;                      //设定一个时间单位的长度为5,范围(1~1024)
  CAN_Init(CAN1, &CAN_InitStructure);
  
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;             //设定过滤器组为屏蔽位模式
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;            //过滤器位宽为32位过滤器一个
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;                          //设定过滤器标识符高位(32为高位段，16位为第一个)
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;                           //设定过滤器标识符低位(32为低位段，16位为第二个)
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh= 0x0000;                       //设定过滤器标识符高位(32为高位段，16位为第一个)
  CAN_FilterInitStructure.CAN_FilterMaskIdLow= 0x0000;                        //设定过滤器标识符低位(32为低位段，16位为第二个)
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;        //过滤器FIFO0指向过滤器0
  CAN_FilterInitStructure.CAN_FilterNumber = 1;                               //指定待初始化的过滤器,范围1~13
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;                      //使能过滤器
  CAN_FilterInit(&CAN_FilterInitStructure);
  
  
    
    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE); //FIF0消息挂号中断允许
  
  //Usart1 NVIC 配置
  NVIC_InitStruct.NVIC_IRQChannel = CAN1_RX1_IRQn;//CAN1_RX0中断向量表中开启
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;		//子优先级3

	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStruct);	//根据指定的参数初始化VIC寄存器
}

//CAN发送帧构成
void CAN_TxMessageInit(uint32_t std_id, uint32_t ext_id, uint8_t ide, uint8_t rtr, uint8_t dlc, uint8_t *pdata)
{
    uint8_t i;
    assert_param(dlc>8);      
    CanTxMessage.StdId = std_id&0x7ff; //设定标准标识符0~0x7ff  11位
    CanTxMessage.ExtId = ext_id&0x3ffff; //设定额外标识符0~0x3ffff 18位
    CanTxMessage.IDE = ide; //输出标识符类型,STD(标准标识符)或EXT(额外标识符)
    CanTxMessage.RTR = rtr; //输出帧类型,DATA(数据帧)或者REMOTE(远程帧)
    CanTxMessage.DLC = dlc; //帧长度，0~8
    for(i=0; i<dlc; i++)
    {
        CanTxMessage.Data[i] = *(pdata+i);
    }
}

//CAN中断接收函数
void CAN1_RX1_IRQHandler(void)
{
    ITStatus Status;
    uint8_t rdata[8];
    Status = CAN_GetITStatus(CAN1, CAN_IT_FMP0);             //判断接受到过滤器中断信号
    
    if(Status == SET)
    {
        CAN_Receive(CAN1, CAN_FIFO0, &CanRxMessage);        //接收一个CAN报文
        memcpy(rdata, &(CanRxMessage.Data[0]), 8);            //将接收到的数据转存到rdata数组中
    }
    
    CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
}


