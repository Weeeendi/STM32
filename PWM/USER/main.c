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
        //Ê¹ÄÜGPIOC£¬TIM3
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
        GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);//¸Ä±äÖ¸¶¨¹Ü½ÅµÄÓ³Éä
=======


/************************************************
 ALIENTEK æˆ˜èˆ°STM32F103å¼€å‘æ¿å®éªŒ0
 å·¥ç¨‹æ¨¡æ¿
 æ³¨æ„ï¼Œè¿™æ˜¯æ‰‹å†Œä¸­çš„æ–°å»ºå·¥ç¨‹ç« èŠ‚ä½¿ç”¨çš„mainæ–‡ä»¶ 
 æŠ€æœ¯æ”¯æŒï¼šwww.openedv.com
 æ·˜å®åº—é“ºï¼šhttp://eboard.taobao.com 
 å…³æ³¨å¾®ä¿¡å…¬ä¼—å¹³å°å¾®ä¿¡å·ï¼š"æ­£ç‚¹åŸå­"ï¼Œå…è´¹è·å–STM32èµ„æ–™ã€‚
 å¹¿å·å¸‚æ˜Ÿç¿¼ç”µå­ç§‘æŠ€æœ‰é™å…¬å¸  
 ä½œè€…ï¼šæ­£ç‚¹åŸå­ @ALIENTEK
************************************************/


int main(void)
 {	    static u16 dutyCycle=0 ;
   
   
        GPIO_InitTypeDef GPIO_InitStructure;
        TIM_TimeBaseInitTypeDef TIM_TImeBaseStructure;
        TIM_OCInitTypeDef  TIM_OCInitStructure;
        //ä½¿èƒ½GPIOAï¼ŒTIM2
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
   
>>>>>>> bcbc5beb9b0470e46763122a9df4696249cf433f
   
        //GPIOçš„é…ç½®ï¼Œå®˜æ–¹åº“æœ‰ç»™å‡ºéœ€è¦é…ç½®çš„ä¸€äº›å‚æ•°ï¼Œå¦‚æœå¿˜è®°äº†ï¼Œå‚ç…§ä¸€ä¸‹å³å¯ï¼Œæˆ‘è¿™é‡Œé…ç½®çš„æ˜¯GPIOA_Pin_1
        
   
        GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
        GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
        GPIO_Init(GPIOC,&GPIO_InitStructure);
   
        	

<<<<<<< HEAD
        //ÅäÖÃTIM2µÄÊ±ÖÓÊä³öÆµÂÊ£¬ÒÔ¼°ÆäËüÏà¹Ø²ÎÊı³õÊ¼»¯
        TIM_TImeBaseStructure.TIM_Prescaler=7200-1;//ÉèÖÃPWMµÄÆµÂÊ
        TIM_TImeBaseStructure.TIM_CounterMode=0;
        TIM_TImeBaseStructure.TIM_Period=99;
        TIM_TimeBaseInit(TIM3,&TIM_TImeBaseStructure);
=======
        //é…ç½®TIM2çš„æ—¶é’Ÿè¾“å‡ºé¢‘ç‡ï¼Œä»¥åŠå…¶å®ƒç›¸å…³å‚æ•°åˆå§‹åŒ–
        TIM_TImeBaseStructure.TIM_Prescaler=0;//è®¾ç½®PWMçš„é¢‘ç‡
        TIM_TImeBaseStructure.TIM_CounterMode=0;
        TIM_TImeBaseStructure.TIM_Period=7200-1;
        TIM_TimeBaseInit(TIM2,&TIM_TImeBaseStructure);
>>>>>>> bcbc5beb9b0470e46763122a9df4696249cf433f


        //è®¾ç½®PWMçš„è¾“å‡ºæ–¹å¼
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
<<<<<<< HEAD
        TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
        TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;   
        //ÅäÖÃÕ¼¿Õ±È

        TIM_OC2Init(TIM3,&TIM_OCInitStructure);//³õÊ¼»¯TIMxÔÚ CCR2 ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
				
        TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable); //Ê¹ÄÜTIMxÔÚ CCR1 ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	      TIM_ARRPreloadConfig(TIM3,ENABLE);//Ê¹ÄÜÔ¤×°ÔØ¼Ä´æÆ÷
				
        TIM_Cmd(TIM3,ENABLE); //Ê¹ÄÜ¶¨Ê±Æ÷
        
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
       
       
        //é…ç½®å ç©ºæ¯”
        //TIM_OCInitStructure.TIM_Pulse=20;

        TIM_OC2Init(TIM2,&TIM_OCInitStructure);
        TIM_ForcedOC1Config(TIM2,TIM_ForcedAction_Active);
        TIM_Cmd(TIM2,ENABLE);//ä½¿èƒ½å®šæ—¶å™¨
        TIM_CtrlPWMOutputs(TIM2,ENABLE);//ä½¿èƒ½PWMå‘ç”Ÿå™¨
        
        
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
       //¶¨Òå´íÎó×´Ì¬±äÁ¿
       ErrorStatus HSEStartUpStatus;
       //½«RCC¼Ä´æÆ÷ÖØĞÂÉèÖÃÎªÄ¬ÈÏÖµ
       RCC_DeInit();
       //´ò¿ªÍâ²¿¸ßËÙÊ±ÖÓ¾§Õñ
       RCC_HSEConfig(RCC_HSE_ON);
       //µÈ´ıÍâ²¿¸ßËÙÊ±ÖÓ¾§Õñ¹¤×÷
       HSEStartUpStatus = RCC_WaitForHSEStartUp();
       if(HSEStartUpStatus == SUCCESS)
       {
              //ÉèÖÃAHBÊ±ÖÓ(HCLK)ÎªÏµÍ³Ê±ÖÓ
              RCC_HCLKConfig(RCC_SYSCLK_Div1);
              //ÉèÖÃ¸ßËÙAHBÊ±ÖÓ(APB2)ÎªHCLKÊ±ÖÓ
              RCC_PCLK2Config(RCC_HCLK_Div1);
              //ÉèÖÃµÍËÙAHBÊ±ÖÓ(APB1)ÎªHCLKµÄ2·ÖÆµ
              RCC_PCLK1Config(RCC_HCLK_Div2);
              //ÉèÖÃFLASH´úÂëÑÓÊ±
              FLASH_SetLatency(FLASH_Latency_2);
               //Ê¹ÄÜÔ¤È¡Ö¸»º´æ
              FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
              //ÉèÖÃPLLÊ±ÖÓ£¬ÎªHSEµÄ9±¶Æµ 8MHz * 9 = 72MHz
              RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
              //Ê¹ÄÜPLL
              RCC_PLLCmd(ENABLE);
              //µÈ´ıPLL×¼±¸¾ÍĞ÷
              while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
              //ÉèÖÃPLLÎªÏµÍ³Ê±ÖÓÔ´
              RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
              //ÅĞ¶ÏPLLÊÇ·ñÊÇÏµÍ³Ê±ÖÓ
              while(RCC_GetSYSCLKSource() != 0x08);
       }
       //¿ªÆôTIM2µÄÊ±ÖÓ
       RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
       //¿ªÆôGPIOBµÄÊ±ÖÓºÍ¸´ÓÃ¹¦ÄÜ
       RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
}

