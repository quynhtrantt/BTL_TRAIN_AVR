#include "test_lcd_3.h"
#include "BSP_TIMER.h"
#include "BSP_LCD.h"
#include "APP_LCD_3.h"
#include "APP_BUTTON.h"

#include <stdint.h>
#include <stdio.h>

extern uint8_t set_temp ;
void TEST_LCD_printf()
{   
    app_LCD_3_update();
    LCD_GotoXY(0, 0);
    LCD_PutString("Set Temp: ");
    LCD_PutChar((set_temp / 10) + '0');
    LCD_PutChar((set_temp % 10) + '0');
    LCD_PutString(" C");
}