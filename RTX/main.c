/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#include "STM32F10x.h"
#include <cmsis_os.h>
#include "led.h"

/*----------------------------------------------------------------------------
  Simple delay routine
 *---------------------------------------------------------------------------*/
void delay (unsigned int count)
{
unsigned int index;

	for(index =0;index<count;index++)
	{
		;
	}
}

/*----------------------------------------------------------------------------
  Flash LED 1
 *---------------------------------------------------------------------------*/
void Thread_LED1(void const* argument)
{
  for(;;)
  {
    LED_On(0);
    delay(1500);
    LED_Off(0);
    delay(1500);
  }
}

/*----------------------------------------------------------------------------
  Flash LED 2
 *---------------------------------------------------------------------------*/
void Thread_LED2(void const* argument)
{
  for(;;)
  {
    LED_On(1);
    delay(1500);
    LED_Off(1);
    delay(1500);
  }
}

osThreadId mai_ID,Led_ID1,Led_ID2;
//osThreadDef(Thread_LED1,osPriorityAboveNormal,1,0);
osThreadDef(Thread_LED2,osPriorityNormal,2,0);
/*
 * main: initialize and start the system
 */
int main (void) {
  osKernelInitialize ();                    // initialize CMSIS-RTOS
  LED_Initialize();
  // initialize peripherals here
 // Led_ID1 = osThreadCreate(osThread(Thread_LED1),NULL);
  Led_ID2 = osThreadCreate(osThread(Thread_LED2),NULL);
  // create 'thread' functions that start executing,
  
  // example: tid_name = osThreadCreate (osThread(name), NULL);

  osKernelStart();                         // start thread execution 
  while(1);
  
}

