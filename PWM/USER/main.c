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


int main(void)
 {	    static u16 dutyCycle=0 ;
   
   
        GPIO_InitTypeDef GPIO_InitStructure;
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
        TIM_TImeBaseStructure.TIM_Prescaler=0;//����PWM��Ƶ��
        TIM_TImeBaseStructure.TIM_CounterMode=0;
        TIM_TImeBaseStructure.TIM_Period=7200-1;
        TIM_TimeBaseInit(TIM2,&TIM_TImeBaseStructure);


        //����PWM�������ʽ
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
       
       
        //����ռ�ձ�
        //TIM_OCInitStructure.TIM_Pulse=20;

        TIM_OC2Init(TIM2,&TIM_OCInitStructure);
        TIM_ForcedOC1Config(TIM2,TIM_ForcedAction_Active);
        TIM_Cmd(TIM2,ENABLE);
        TIM_CtrlPWMOutputs(TIM2,ENABLE);
        
        
        while(1)
        {
              while (dutyCycle < 9999)
            {
            dutyCycle ++;
          //	  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, dutyCycle);//�޸�ռ�ձȺ�ˢ�¼Ĵ�������
              TIM2->CCR2 = dutyCycle;
		  
            }
    
              while (dutyCycle)
              {
                dutyCycle --;
            //  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, dutyCycle);
                TIM2->CCR2 = dutyCycle;
              }
          
        }
 }

