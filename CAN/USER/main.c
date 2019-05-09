#include "stm32f10x.h"
#include "led.h"

/************************************************
 ALIENTEK ս��STM32F103������ʵ��0
 ����ģ��
 ע�⣬�����ֲ��е��½������½�ʹ�õ�main�ļ� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 �������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
#include <stdio.h>
#include "Systick.h"
#include "can.h"
#include "string.h"

extern CanRxMsg CanRxMessage;
extern CanTxMsg CanTxMessage;

uint8_t tdata[8] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37};
uint8_t rdata[8];

int main(void)
{   
    

    
    LED_Init();
    CAN1_Init();   //Ӳ����ʼ��
    CAN_TxMessageInit(0x011, 0x0000, CAN_ID_STD,CAN_RTR_DATA, sizeof(tdata), tdata);//����CAN����
    CAN_Transmit(CAN1, &CanTxMessage);  //����CAN����
    
    GPIO_ResetBits(LED_PORT, GPIO_Pin_1);
    delay_ms(500);
    GPIO_SetBits(LED_PORT, GPIO_Pin_1);
    delay_ms(500);

    while(1)
    {    
        if(CanRxMessage.StdId == 0x11 && CanRxMessage.DLC == sizeof(tdata))  //�жϽ��յ��ı���
        {                                                                                                                                   
            if(strncmp((char *)tdata, (char *)rdata, sizeof(rdata)) == 0)
            {
                GPIO_ResetBits(LED_PORT, GPIO_Pin_1);
                printf("stdID is %x, DIC is %x, receive data is %s \r\n", 
                CanRxMessage.StdId, CanRxMessage.DLC, rdata);
            }
            memset(&CanRxMessage, 0, sizeof(CanRxMessage));     //������յ��ı���            
            CAN_Transmit(CAN1, &CanTxMessage);                  //����CAN����
        } 
        delay_ms(500);
        GPIO_SetBits(LED_PORT, GPIO_Pin_1);
        delay_ms(500);
    }
}