
#ifndef USART_H
#define USART_H
#include "stm32f10x.h"
#include "system.h" 
#include "stdio.h" 
void uart1_init(int Buadrate);
void Send_Data(u8 *s);


#endif


