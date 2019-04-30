/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#include "STM32F10x.h"
#include <cmsis_os.h>
#include "led.h"



/*----------------------------------------------------------------------------
  Flash LED 1
 *---------------------------------------------------------------------------*/
void Thread_LED1(void const* argument)
{
  while(1)
  {
    LED_On(0);
    osDelay(200);
    LED_Off(0);
    osDelay(200);
  }
}

/*----------------------------------------------------------------------------
  Flash LED 2
 *---------------------------------------------------------------------------*/
void Thread_LED2(void const* argument)
{
  while(1)
  {
    LED_On(1);
    osDelay(500);
    LED_Off(1);
    osDelay(200);
  }
}

osThreadId mai_ID,Led_ID1,Led_ID2;
osThreadDef(Thread_LED1,osPriorityNormal,1,0);
osThreadDef(Thread_LED2,osPriorityNormal,1,0);
/*
 * main: initialize and start the system
 */
int main (void) {
  osKernelInitialize ();                    // initialize CMSIS-RTOS
  LED_Initialize();
  // initialize peripherals here
  Led_ID2 = osThreadCreate(osThread(Thread_LED1),NULL);
  Led_ID1 = osThreadCreate(osThread(Thread_LED2),NULL);
  // create 'thread' functions that start executing,
  
  // example: tid_name = osThreadCreate (osThread(name), NULL);

  osKernelStart();                         // start thread execution 
  while(1);
  
}

