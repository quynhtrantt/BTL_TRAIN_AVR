#include "BOARD.h"
#include "APP_DHT.h"
#include "BSP_DHT.h"
#include "BSP_LCD.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "BSP_DHT.h"
#include "BSP_LCD.h"
#include "BSP_TIMER.h"

int main(void)
{
	uint8_t humidity, temperature, err;

	BSP_LCD_Init();
	BSP_DHT_Init();

	_delay_ms(1000);   /* DHT ?n ??nh sau c?p ngu?n */

	LCD_GotoXY(0, 0);
	LCD_PutString("DHT11 TEST");

	while (1)
	{
		cli();
		err = BSP_DHT_Read(&humidity, &temperature);
		sei();

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

		_delay_ms(2000);   /* DHT11 c?n >=1s gi?a 2 l?n ??c */
	}
}