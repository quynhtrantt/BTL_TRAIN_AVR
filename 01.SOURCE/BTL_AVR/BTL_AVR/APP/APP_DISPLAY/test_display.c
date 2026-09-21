#include "avr/io.h"
#include "BSP_LCD.h"
#include "app_display.h"
#include "DATA_DHT.h"
#include "APP_DHT.h"
#include "util/delay.h"
#include "BSP_BUTTON.h"
#include "APP_BUTTON.h"
#include "BSP_TIMER.h"
#include <avr/interrupt.h>
#include "APP_LCD_3.h"

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

extern uint8_t set_temp;
extern uint8_t temperature;
extern uint8_t humidity;

int main(void)
{
	
	App_Display_Init();
	app_dht_init();
	bsp_button_init();
	BSP_Timer1_Init();
	sei();

	while (1)
	{
		
		app_dht_update();
		App_Display_SetTemperature(data_dht_get_temperature());
		App_Display_SetHumidity(data_dht_get_humidity());	
		
		
		app_button_update();
		app_LCD_3_update();
		App_Display_SetCount(set_temp);
		
		if (bsp_button_page_get_state() == BUTTON_PRESSED)
		{
			App_Display_NextPage();	
		}
	}

	return 0;
}