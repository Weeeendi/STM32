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


int main(void)
 {	    static u16 dutyCycle=0 ;
   
   
        GPIO_InitTypeDef GPIO_InitStructure;
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
        TIM_TImeBaseStructure.TIM_Prescaler=0;//设置PWM的频率
        TIM_TImeBaseStructure.TIM_CounterMode=0;
        TIM_TImeBaseStructure.TIM_Period=7200-1;
        TIM_TimeBaseInit(TIM2,&TIM_TImeBaseStructure);


        //设置PWM的输出方式
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
       
       
        //配置占空比
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
          //	  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, dutyCycle);//修改占空比后刷新寄存器设置
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

