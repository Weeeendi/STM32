#include "stm32f10x.h"
<<<<<<< HEAD
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
=======


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
   
>>>>>>> bcbc5beb9b0470e46763122a9df4696249cf433f
   
        //GPIO的配置，官方库有给出需要配置的一些参数，如果忘记了，参照一下即可，我这里配置的是GPIOA_Pin_1
        
   
        GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
        GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
        GPIO_Init(GPIOC,&GPIO_InitStructure);
   
        	

<<<<<<< HEAD
        //����TIM2��ʱ�����Ƶ�ʣ��Լ�������ز�����ʼ��
        TIM_TImeBaseStructure.TIM_Prescaler=7200-1;//����PWM��Ƶ��
        TIM_TImeBaseStructure.TIM_CounterMode=0;
        TIM_TImeBaseStructure.TIM_Period=99;
        TIM_TimeBaseInit(TIM3,&TIM_TImeBaseStructure);
=======
        //配置TIM2的时钟输出频率，以及其它相关参数初始化
        TIM_TImeBaseStructure.TIM_Prescaler=0;//设置PWM的频率
        TIM_TImeBaseStructure.TIM_CounterMode=0;
        TIM_TImeBaseStructure.TIM_Period=7200-1;
        TIM_TimeBaseInit(TIM2,&TIM_TImeBaseStructure);
>>>>>>> bcbc5beb9b0470e46763122a9df4696249cf433f


        //设置PWM的输出方式
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
<<<<<<< HEAD
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
=======
       
       
        //配置占空比
        //TIM_OCInitStructure.TIM_Pulse=20;

        TIM_OC2Init(TIM2,&TIM_OCInitStructure);
        TIM_ForcedOC1Config(TIM2,TIM_ForcedAction_Active);
        TIM_Cmd(TIM2,ENABLE);//使能定时器
        TIM_CtrlPWMOutputs(TIM2,ENABLE);//使能PWM发生器
        
        
        while(1)
        {
              while (dutyCycle < 9999)
            {
            dutyCycle ++;
              TIM2->CCR2 = dutyCycle;
		  
            }
    
              while (dutyCycle)
              {
                dutyCycle --;
                TIM2->CCR2 = dutyCycle;
              }
          
>>>>>>> bcbc5beb9b0470e46763122a9df4696249cf433f
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

