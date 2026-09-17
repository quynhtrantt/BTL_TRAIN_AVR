#include "avr/io.h"
#include "BSP_LCD.h"
#include "LCD.h"
#include "BSP_BUTTON.h"
#include "APP_BUTTON/APP_BUTTON.h"
#include "DATA_BUTTON.h"


int main(void)
{

		
	BSP_LCD_Init();
	LCD_GotoXY(0, 0);
	LCD_PutString("qiqi");
	LCD_GotoXY(0, 1);
	LCD_PutString("is thuy quynh");
	
    while (1) 
    {
		app_button_update();
		if(data_button_get_state() == BUTTON_PRESSED)
		{
			
		}
		else
		{
			
		}
    }
	return 0;
}

