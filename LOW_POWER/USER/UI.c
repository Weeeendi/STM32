
#include "main.h"

#define USE_GLCD 1

#if (USE_GLCD==1)
#include "tftlcd.h"
#include "LCD_Config.h"

#endif

bool UI_Initialize(void) {
#if (USE_GLCD == 1)
    TFTLCD_Init();
    FRONT_COLOR=LCD_COLOR_BLUE;
    LCD_Clear(LCD_COLOR_WHITE);
    LCD_ShowString(0,0*20,tftlcd_data.width,tftlcd_data.height,16," CAN Example");
    LCD_ShowString(0,1*20,tftlcd_data.width,tftlcd_data.height,16,"Tx data:    ");
    LCD_ShowString(0,2*20,tftlcd_data.width,tftlcd_data.height,16,"            ");
    LCD_ShowString(0,3*20,tftlcd_data.width,tftlcd_data.height,16,"Rx data:    ");
    LCD_ShowString(0,4*20,tftlcd_data.width,tftlcd_data.height,16,"            ");
    LCD_ShowString(0,5*20,tftlcd_data.width,tftlcd_data.height,16,"            ");
    LCD_ShowString(0,6*20,tftlcd_data.width,tftlcd_data.height,16,"Author:Wen Di");

#endif
    printf("CAN1 Example\n");
    return true;
}

