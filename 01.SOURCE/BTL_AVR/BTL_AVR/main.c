#include "avr/io.h"
#include "BSP_LCD.h"
#include "LCD.h"
#include "BSP_LED.h"


int main(void)
{
	BSP_LCD_Init();
	LCD_GotoXY(0, 0);
	LCD_PutString("qiqi");
	LCD_GotoXY(0, 1);
	LCD_PutString("is thuy quynh");
	
	BSP_LED_Init();
	BSP_LED_On(); 
	
    while (1) 
    {
    }
	return 0;
}

