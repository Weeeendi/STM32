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
    CAN1_Init();   //硬件初始化
    CAN_TxMessageInit(0x011, 0x0000, CAN_ID_STD,CAN_RTR_DATA, sizeof(tdata), tdata);//生成CAN报文
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
