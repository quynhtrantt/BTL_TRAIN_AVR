#include "avr/io.h"
#include "BSP_LCD.h"
#include "app_display.h"
#include "DATA_DHT.h"
#include "util/delay.h"

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#define BUTTON_PAGE_ID  0

int main(void)
{
	App_Display_Init();

	while (1)
	{
			DDRD &= ~(1 << PB1);
			PORTB |= (1 << PB1);
		uint8_t current_temp = data_dht_get_temperature();
		uint8_t current_humi = data_dht_get_humidity();
		
		App_Display_SetTemperature(current_temp);
		App_Display_SetHumidity(current_humi);
		
	if ((PINB & (1 << PB1)) == 0)
	{
		_delay_ms(20); 
		if ((PINB & (1 << PB1)) == 0) 
		{
			App_Display_NextPage(); 
			
		}
	}

	}
	return 0;
}