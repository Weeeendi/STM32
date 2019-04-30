#include "led.h"
#include "GPIO_STM32F10x.h"

const GPIO_PIN_ID Pin_LED[] = {
  { GPIOC, 0 },
  { GPIOC, 1 },
  { GPIOC, 2 },
  { GPIOC, 3 },
  { GPIOC, 4 },
  { GPIOC, 5 },
  { GPIOC, 6 },
  { GPIOC, 7 },
};
#define LED_COUNT (sizeof(Pin_LED)/sizeof(GPIO_PIN_ID))

/**
  \fn          int32_t LED_Initialize (void)
  \brief       Initialize LEDs
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/

int32_t LED_Initialize(void){
  uint16_t n;
  for(n=0;n<LED_COUNT;n++){
    GPIO_PortClock(Pin_LED[n].port,true);
    GPIO_PinWrite    (Pin_LED[n].port, Pin_LED[n].num, 1);
    GPIO_PinConfigure(Pin_LED[n].port, Pin_LED[n].num,
                      GPIO_OUT_PUSH_PULL, 
                      GPIO_MODE_OUT2MHZ);  
  }
  return 0;
}

/**
  \fn          int32_t LED_UnInitialize (void)
  \brief       UnInitialize LEDs
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
int32_t  LED_Uninitialize (void){
   uint16_t n;

    GPIO_PinConfigure(Pin_LED[n].port, Pin_LED[n].num,
                      GPIO_IN_FLOATING,GPIO_MODE_INPUT);  
  return 0;
  
}
/**
  \fn          int32_t  LED_On   (void)
  \brief       Turn On the single LED
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
int32_t  LED_On           (uint32_t num){
  GPIO_PinWrite    (Pin_LED[num].port, Pin_LED[num].num, 0);
  return 0;
}

/**
  \fn          int32_t  LED_Off   (void)
  \brief       Turn Off the single LED
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
int32_t  LED_Off           (uint32_t num){
  GPIO_PinWrite (Pin_LED[num].port, Pin_LED[num].num, 1);
  return 0;
}


/**
  \fn          int32_t  LED_Setout   (void)
  \brief       Control all LEDs with the bit vector
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
int32_t LED_SetOut(uint32_t val){
   uint32_t n;
  for(n=0;n<LED_COUNT;n++){
  if(val&(1<<n)){
    LED_On(n);
  }
  else {
    LED_Off(n);
  }
}
  return 0;
}
        
/**
  \fn          uint32_t LED_GetCount (void)
  \brief       Get number of available LEDs on evaluation hardware
  \return      Number of available LEDs
*/
uint32_t LED_GetCount (void){
  return LED_COUNT;
}
