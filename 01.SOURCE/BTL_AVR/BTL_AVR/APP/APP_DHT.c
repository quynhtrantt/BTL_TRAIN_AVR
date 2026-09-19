/*
 * APP_DHT.c
 *
 * Created: 9/18/2026 4:26:43 PM
 *  Author: HP
 */ 
#include "APP_DHT.h"

#include "BSP_DHT.h"
#include "DATA_DHT.h"
#include "BSP_Timer.h"

#define DHT_READ_INTERVAL_MS    2000UL

static uint32_t last_read_time = 0;

void app_dht_init(void)
{
	BSP_DHT_Init();
	last_read_time = BSP_GetSysTimeMs();
}

void app_dht_update(void)
{
    uint8_t humidity;
    uint8_t temperature;

    uint32_t current_time;

    current_time = BSP_GetSysTimeMs();

	//Ch?a t?i th?i gian ??c ti?p theo
    if ((uint32_t)(current_time - last_read_time)
        < DHT_READ_INTERVAL_MS)
    {
        return;
    }

	//?ã t?i th?i gian ??c DHT
    last_read_time = current_time;

	//??c DHT
    if (BSP_DHT_Read(&humidity, &temperature))
    {
        data_dht_set_humidity(humidity);
        data_dht_set_temperature(temperature);
    }
}