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
//  USART_InitStruct.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
//  
//  USART_Init(USART1,&USART_InitStruct);
//  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
//  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
  
}

void CAN1_MODE_Config(void)
{
  CAN_InitTypeDef CAN_InitStructure;
  CAN_FilterInitTypeDef CAN_FilterInitStructure;
  NVIC_InitTypeDef NVIC_InitStruct;
   
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
  CAN_DeInit(CAN1);
  
  CAN_InitStructure.CAN_ABOM = DISABLE;                     //����ģʽ�����ʵ��
  CAN_InitStructure.CAN_AWUM = DISABLE;                     //�������
  CAN_InitStructure.CAN_TTCM = DISABLE;                     //��ֹʱ�䴥��ͨ��ģʽ
  CAN_InitStructure.CAN_NART = ENABLE;                      //��ֹ�Զ��ش�
  CAN_InitStructure.CAN_TXFP = DISABLE;                     //���ȼ��ɱ��ĵı�ʶ��������
  CAN_InitStructure.CAN_RFLM = DISABLE;                     //�������ʱFIFO����������һ���յ��ı��ĸ���ԭ�б���
  CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack;           //CANӲ����������ģʽ
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;                  //����ͬ����Ծ���Ϊ2��ʱ�䵥λ
  CAN_InitStructure.CAN_BS1 = CAN_BS1_8tq;                  //ʱ���Ϊ8��ʱ�䵥λ
  CAN_InitStructure.CAN_BS2 = CAN_BS2_7tq;                  //ʱ���Ϊ7��ʱ�䵥λ
  CAN_InitStructure.CAN_Prescaler = 5;                      //�趨һ��ʱ�䵥λ�ĳ���Ϊ5,��Χ(1~1024)
  CAN_Init(CAN1, &CAN_InitStructure);
  
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;             //�趨��������Ϊ����λģʽ
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;            //������λ��Ϊ32λ������һ��
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;                          //�趨��������ʶ����λ(32Ϊ��λ�Σ�16λΪ��һ��)
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;                           //�趨��������ʶ����λ(32Ϊ��λ�Σ�16λΪ�ڶ���)
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh= 0x0000;                       //�趨��������ʶ����λ(32Ϊ��λ�Σ�16λΪ��һ��)
  CAN_FilterInitStructure.CAN_FilterMaskIdLow= 0x0000;                        //�趨��������ʶ����λ(32Ϊ��λ�Σ�16λΪ�ڶ���)
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;        //������FIFO0ָ�������0
  CAN_FilterInitStructure.CAN_FilterNumber = 1;                               //ָ������ʼ���Ĺ�����,��Χ1~13
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;                      //ʹ�ܹ�����
  CAN_FilterInit(&CAN_FilterInitStructure);
  
  
    
    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE); //FIF0��Ϣ�Һ��ж�����
  
  //Usart1 NVIC ����
  NVIC_InitStruct.NVIC_IRQChannel = CAN1_RX1_IRQn;//CAN1_RX0�ж��������п���
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3

	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStruct);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
}

//CAN����֡����
void CAN_TxMessageInit(uint32_t std_id, uint32_t ext_id, uint8_t ide, uint8_t rtr, uint8_t dlc, uint8_t *pdata)
{
    uint8_t i;
    assert_param(dlc>8);      
    CanTxMessage.StdId = std_id&0x7ff; //�趨��׼��ʶ��0~0x7ff  11λ
    CanTxMessage.ExtId = ext_id&0x3ffff; //�趨�����ʶ��0~0x3ffff 18λ
    CanTxMessage.IDE = ide; //�����ʶ������,STD(��׼��ʶ��)��EXT(�����ʶ��)
    CanTxMessage.RTR = rtr; //���֡����,DATA(����֡)����REMOTE(Զ��֡)
    CanTxMessage.DLC = dlc; //֡���ȣ�0~8
    for(i=0; i<dlc; i++)
    {
        CanTxMessage.Data[i] = *(pdata+i);
    }
}

//CAN�жϽ��պ���
void CAN1_RX1_IRQHandler(void)
{
    ITStatus Status;
    uint8_t rdata[8];
    Status = CAN_GetITStatus(CAN1, CAN_IT_FMP0);             //�жϽ��ܵ��������ж��ź�
    
    if(Status == SET)
    {
        CAN_Receive(CAN1, CAN_FIFO0, &CanRxMessage);        //����һ��CAN����
        memcpy(rdata, &(CanRxMessage.Data[0]), 8);            //�����յ�������ת�浽rdata������
    }
    
    CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
}


