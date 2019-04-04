#include "stm32f10x.h"


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

#include "digital.h"
#include "Systick.h"

u8 digital_table[]={0xc0,0xf9,0xA4,0xB0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};//0-F 共阳

int main(void)
 {	    GPIO_InitTypeDef GPIO_InitStructure;
        TIM_TimeBaseInitTypeDef TIM_TImeBaseStructure;
        TIM_OCInitTypeDef  TIM_OCInitStructure;
        //使能GPIOA，TIM2
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
   
   
        //GPIO的配置，官方库有给出需要配置的一些参数，如果忘记了，参照一下即可，我这里配置的是GPIOA_Pin_1
        
   
        GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
        GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
        GPIO_Init(GPIOA,&GPIO_InitStructure);
   
        

        //配置TIM2的时钟输出频率，以及其它相关参数初始化
        TIM_TImeBaseStructure.TIM_Prescaler=360-1;//设置PWM的频率
        TIM_TImeBaseStructure.TIM_CounterMode=0;
        TIM_TImeBaseStructure.TIM_Period=100;
        TIM_TimeBaseInit(TIM2,&TIM_TImeBaseStructure);


        //设置PWM的输出方式
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
        TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
        TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
        TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
        TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;   
        //配置占空比
        TIM_OCInitStructure.TIM_Pulse=20;

        TIM_OC2Init(TIM2,&TIM_OCInitStructure);
        TIM_ForcedOC1Config(TIM2,TIM_ForcedAction_Active);
        TIM_Cmd(TIM2,ENABLE);
        TIM_CtrlPWMOutputs(TIM2,ENABLE);
        
        
        while(1)
        {
                ;
        }
 }

