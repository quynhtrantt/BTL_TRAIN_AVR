#include "BOARD.h"
#include "APP_DHT.h"
#include "DATA_DHT.h"
#include "BSP_LCD.h"
#include "BSP_TIMER.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>


int main(void)
{
	uint8_t humidity;
	uint8_t temperature;
	uint8_t status;

	BSP_LCD_Init();
	BSP_Timer1_Init();     /* c?p m?c th?i gian cho BSP_GetSysTimeMs() */

	app_dht_init();

	sei();

	LCD_GotoXY(0, 0);
	LCD_PutString("DHT11 MONITOR");

	while (1)
	{
		/* Layer APP t? quy?t ??nh khi nào c?n ??c l?i DHT (2s/l?n) */
		app_dht_update();

		/* Layer MAIN ch? l?y d? li?u ?ã l?u trong DATA ?? hi?n th? */
		humidity    = data_dht_get_humidity();
		temperature = data_dht_get_temperature();
		status      = app_dht_get_read_status();

		LCD_GotoXY(0, 1);

		if (status == 1)
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
			LCD_PutString("DHT ERROR     ");
		}
	}
}
