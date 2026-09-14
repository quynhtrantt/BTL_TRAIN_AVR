#include "avr/io.h"
#include "BSP_LCD.h"
#include "LCD.h"
int main(void)
{
	BSP_LCD_Init();
	LCD_GotoXY(0, 0);
	LCD_PutString("qiqi");
	LCD_GotoXY(0, 1);
	LCD_PutString("is thuy quynh");
	
    while (1) 
    {
    }
	return 0;
}

