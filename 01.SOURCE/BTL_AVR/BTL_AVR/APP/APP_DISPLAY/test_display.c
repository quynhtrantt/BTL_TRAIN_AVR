#include "avr/io.h"
#include "BSP_LCD.h"
#include "app_display.h"
#include "DATA_DHT.h"
#include "APP_DHT.h"
#include "util/delay.h"
#include "BSP_BUTTON.h"
#include "APP_BUTTON.h"


#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#define BUTTON_PAGE_ID  0

int main(void)
{
	App_Display_Init();
	

	while (1)
	{
		
		App_Display_SetTemperature(data_dht_get_temperature());
		App_Display_SetHumidity(data_dht_get_humidity());
		
		if (bsp_button_start_get_state() == BUTTON_PRESSED)
		{
			 App_Display_NextPage();
			while (bsp_button_start_get_state() == BUTTON_PRESSED);
		}

	}
	return 0;
}