#include "stm32f10x.h"
#include "Systick.h"
void RCC_cfg(void);


int main(void)
 {	    
	      RCC_cfg();
	      GPIO_InitTypeDef GPIO_InitStructure;
        TIM_TimeBaseInitTypeDef TIM_TImeBaseStructure;
        TIM_OCInitTypeDef  TIM_OCInitStructure;
        //使能GPIOC，TIM3
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
        GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);//改变指定管脚的映射
   
        //GPIO的配置，官方库有给出需要配置的一些参数，如果忘记了，参照一下即可，我这里配置的是GPIOA_Pin_1
        
   
        GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
        GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
        GPIO_Init(GPIOC,&GPIO_InitStructure);
   
        	

        //配置TIM2的时钟输出频率，以及其它相关参数初始化
        TIM_TImeBaseStructure.TIM_Prescaler=7200-1;//设置PWM的频率
        TIM_TImeBaseStructure.TIM_CounterMode=0;
        TIM_TImeBaseStructure.TIM_Period=99;
        TIM_TimeBaseInit(TIM3,&TIM_TImeBaseStructure);


        //设置PWM的输出方式
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
        TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
        TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
        TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;   
        //配置占空比

        TIM_OC2Init(TIM3,&TIM_OCInitStructure);//初始化TIMx在 CCR2 上的预装载寄存器
				
        TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable); //使能TIMx在 CCR1 上的预装载寄存器
	      TIM_ARRPreloadConfig(TIM3,ENABLE);//使能预装载寄存器
				
        TIM_Cmd(TIM3,ENABLE); //使能定时器
        
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
       //定义错误状态变量
       ErrorStatus HSEStartUpStatus;
       //将RCC寄存器重新设置为默认值
       RCC_DeInit();
       //打开外部高速时钟晶振
       RCC_HSEConfig(RCC_HSE_ON);
       //等待外部高速时钟晶振工作
       HSEStartUpStatus = RCC_WaitForHSEStartUp();
       if(HSEStartUpStatus == SUCCESS)
       {
              //设置AHB时钟(HCLK)为系统时钟
              RCC_HCLKConfig(RCC_SYSCLK_Div1);
              //设置高速AHB时钟(APB2)为HCLK时钟
              RCC_PCLK2Config(RCC_HCLK_Div1);
              //设置低速AHB时钟(APB1)为HCLK的2分频
              RCC_PCLK1Config(RCC_HCLK_Div2);
              //设置FLASH代码延时
              FLASH_SetLatency(FLASH_Latency_2);
               //使能预取指缓存
              FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
              //设置PLL时钟，为HSE的9倍频 8MHz * 9 = 72MHz
              RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
              //使能PLL
              RCC_PLLCmd(ENABLE);
              //等待PLL准备就绪
              while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
              //设置PLL为系统时钟源
              RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
              //判断PLL是否是系统时钟
              while(RCC_GetSYSCLKSource() != 0x08);
       }
       //开启TIM2的时钟
       RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
       //开启GPIOB的时钟和复用功能
       RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
}

