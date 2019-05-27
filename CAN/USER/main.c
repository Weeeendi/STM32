#include <stdio.h>
#include "stm32f10x.h"
#include "led.h"
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
    CAN1_Init();   //硬件初始化
    CAN1_MODE_Config();
    //生成CAN报文
    CAN_Transmit(CAN1, &CanTxMessage);  //发送CAN报文
    
    GPIO_ResetBits(LED_PORT, GPIO_Pin_1);
    delay_ms(500);
    GPIO_SetBits(LED_PORT, GPIO_Pin_1);
    delay_ms(500);

    while(1)
    {    
        if(CanRxMessage.StdId == 0x11 && CanRxMessage.DLC == sizeof(tdata))  //判断接收到的报文
        {                                                                                                                                   
            if(strncmp((char *)tdata, (char *)rdata, sizeof(rdata)) == 0)
            {
                GPIO_ResetBits(LED_PORT, GPIO_Pin_1);
                printf("stdID is %x, DIC is %x, receive data is %s \r\n", 
                CanRxMessage.StdId, CanRxMessage.DLC, rdata);
            }
            memset(&CanRxMessage, 0, sizeof(CanRxMessage));     //清除接收到的报文            
            CAN_Transmit(CAN1, &CanTxMessage);                  //发送CAN报文
        } 
        delay_ms(500);
        GPIO_SetBits(LED_PORT, GPIO_Pin_1);
        delay_ms(500);
    }
}
