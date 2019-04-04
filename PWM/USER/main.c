#include "stm32f10x.h"


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

#include "digital.h"
#include "Systick.h"

u8 digital_table[]={0xc0,0xf9,0xA4,0xB0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};//0-F ����

int main(void)
 {	    GPIO_InitTypeDef GPIO_InitStructure;
        TIM_TimeBaseInitTypeDef TIM_TImeBaseStructure;
        TIM_OCInitTypeDef  TIM_OCInitStructure;
        //ʹ��GPIOA��TIM2
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
   
   
        //GPIO�����ã��ٷ����и�����Ҫ���õ�һЩ��������������ˣ�����һ�¼��ɣ����������õ���GPIOA_Pin_1
        
   
        GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
        GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
        GPIO_Init(GPIOA,&GPIO_InitStructure);
   
        

        //����TIM2��ʱ�����Ƶ�ʣ��Լ�������ز�����ʼ��
        TIM_TImeBaseStructure.TIM_Prescaler=360-1;//����PWM��Ƶ��
        TIM_TImeBaseStructure.TIM_CounterMode=0;
        TIM_TImeBaseStructure.TIM_Period=100;
        TIM_TimeBaseInit(TIM2,&TIM_TImeBaseStructure);


        //����PWM�������ʽ
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
        TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
        TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
        TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
        TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;   
        //����ռ�ձ�
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

