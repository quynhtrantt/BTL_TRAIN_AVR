#include "BOARD.h"
#include "APP_DHT.h"
#include "BSP_DHT.h"
#include "BSP_LCD.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdint.h>
#include "BSP_TIMER.h"
#include "BSP_BUTTON.h"
#include "APP_BUTTON.h"
#include "APP_LCD_3.h"
#include "test_lcd_3.h"


int main(void)
{
	uint8_t humidity, temperature, err;

	BSP_LCD_Init();
	BSP_DHT_Init();
	BSP_Timer1_Init();
	bsp_button_init();
	sei();
	_delay_ms(1000);   /* DHT ?n ??nh sau c?p ngu?n */

	LCD_GotoXY(0, 0);
	LCD_PutString("DHT11 TEST");
	
	
	while (1)
	{
		TEST_LCD_printf();
		cli();
		err = BSP_DHT_Read(&humidity, &temperature);
		sei();
		TEST_LCD_printf();
		LCD_GotoXY(0, 1);
		
	//?? hi?n th? humidity vs temperature thì ch? c?n g?i tên 2 bi?n ra là ???c
		if (err == 0)
		{
			LCD_PutString("H:");
			LCD_PutChar(humidity / 10 + '0');
			LCD_PutChar(humidity % 10 + '0');
			LCD_PutString(" T:");
			LCD_PutChar(temperature / 10 + '0');
			LCD_PutChar(temperature % 10 + '0');
			LCD_PutString("   ");
		}
		else
		{
			LCD_PutString("ERR:");
			LCD_PutChar(err + '0');
			LCD_PutString("      ");
		}

		_delay_ms(500);   /* DHT11 c?n >=1s gi?a 2 l?n ??c */
	}
}