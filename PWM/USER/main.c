#include "stm32f10x.h"
#include "Systick.h"
void RCC_cfg(void);


int main(void)
 {	    
	      RCC_cfg();
	      GPIO_InitTypeDef GPIO_InitStructure;
        TIM_TimeBaseInitTypeDef TIM_TImeBaseStructure;
        TIM_OCInitTypeDef  TIM_OCInitStructure;
        //ʹ��GPIOC��TIM3
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
        GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);//�ı�ָ���ܽŵ�ӳ��
   
        //GPIO�����ã��ٷ����и�����Ҫ���õ�һЩ��������������ˣ�����һ�¼��ɣ����������õ���GPIOA_Pin_1
        
   
        GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
        GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
        GPIO_Init(GPIOC,&GPIO_InitStructure);
   
        	

        //����TIM2��ʱ�����Ƶ�ʣ��Լ�������ز�����ʼ��
        TIM_TImeBaseStructure.TIM_Prescaler=7200-1;//����PWM��Ƶ��
        TIM_TImeBaseStructure.TIM_CounterMode=0;
        TIM_TImeBaseStructure.TIM_Period=99;
        TIM_TimeBaseInit(TIM3,&TIM_TImeBaseStructure);


        //����PWM�������ʽ
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
        TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
        TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
        TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;   
        //����ռ�ձ�

        TIM_OC2Init(TIM3,&TIM_OCInitStructure);//��ʼ��TIMx�� CCR2 �ϵ�Ԥװ�ؼĴ���
				
        TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable); //ʹ��TIMx�� CCR1 �ϵ�Ԥװ�ؼĴ���
	      TIM_ARRPreloadConfig(TIM3,ENABLE);//ʹ��Ԥװ�ؼĴ���
				
        TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��
        
        while(1)
        {
					  static u8 dir=0;
					  static u16 light = 10;
            if(dir){					
							light++;
							if(light>=75)	dir = 0;	
					  }
						else{
							light--;
							if(light<=10) dir =1;	
						}
            TIM3->CCR2 = light;
						delay_ms(10);
        }
 }

 
void RCC_cfg(void)
{
       //�������״̬����
       ErrorStatus HSEStartUpStatus;
       //��RCC�Ĵ�����������ΪĬ��ֵ
       RCC_DeInit();
       //���ⲿ����ʱ�Ӿ���
       RCC_HSEConfig(RCC_HSE_ON);
       //�ȴ��ⲿ����ʱ�Ӿ�����
       HSEStartUpStatus = RCC_WaitForHSEStartUp();
       if(HSEStartUpStatus == SUCCESS)
       {
              //����AHBʱ��(HCLK)Ϊϵͳʱ��
              RCC_HCLKConfig(RCC_SYSCLK_Div1);
              //���ø���AHBʱ��(APB2)ΪHCLKʱ��
              RCC_PCLK2Config(RCC_HCLK_Div1);
              //���õ���AHBʱ��(APB1)ΪHCLK��2��Ƶ
              RCC_PCLK1Config(RCC_HCLK_Div2);
              //����FLASH������ʱ
              FLASH_SetLatency(FLASH_Latency_2);
               //ʹ��Ԥȡָ����
              FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
              //����PLLʱ�ӣ�ΪHSE��9��Ƶ 8MHz * 9 = 72MHz
              RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
              //ʹ��PLL
              RCC_PLLCmd(ENABLE);
              //�ȴ�PLL׼������
              while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
              //����PLLΪϵͳʱ��Դ
              RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
              //�ж�PLL�Ƿ���ϵͳʱ��
              while(RCC_GetSYSCLKSource() != 0x08);
       }
       //����TIM2��ʱ��
       RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
       //����GPIOB��ʱ�Ӻ͸��ù���
       RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
}

