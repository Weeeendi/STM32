/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::CAN
 * Copyright (c) 2004-2016 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    main.h
 * Purpose: CAN Example main header
 *----------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "Driver_CAN.h"
#include "cmsis_os.h"

extern uint8_t rx_data[8];
extern uint8_t tx_data[8];

extern bool CAN_Initialize (void);
extern void CAN_Thread     (void const *arg);


extern void LCD_Thread(void const *arg);
extern bool UI_Initialize  (void);

extern int32_t LED_Initialize(void);
extern void Thread_LED1(void const *arg);

extern osThreadId LCD_ID;
extern osThreadId CAN_ID;
extern osThreadId LED_ID;

