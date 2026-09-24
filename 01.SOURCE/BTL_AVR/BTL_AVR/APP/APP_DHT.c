#include "APP_DHT.h"

#include "BSP_DHT.h"
#include "DATA_DHT.h"
#include "BSP_Timer.h"
#include "BOARD.h"

#define DHT_READ_INTERVAL_MS    500UL

static uint32_t last_read_time = 0;
static uint8_t read_status = 0;


void app_dht_init(void)
{
	BSP_DHT_Init();

	last_read_time = BSP_GetSysTimeMs();

	/* Ban ??u ch?a ??c DHT */
	read_status = 0;
}


void app_dht_update(void)
{
	uint8_t humidity;
	uint8_t temperature;

	uint32_t current_time;

	current_time = BSP_GetSysTimeMs();

	if ((current_time - last_read_time) >= DHT_READ_INTERVAL_MS)
	{
		last_read_time = current_time;

		if (BSP_DHT_Read(&humidity, &temperature) == 0)
		{
			/* ??c DHT thành công */

			data_dht_set_humidity(humidity);
			data_dht_set_temperature(temperature);

			read_status = 1;
		}
		else
		{
			/* ??c DHT th?t b?i */

			read_status = 0;
		}
	}
}


uint8_t app_dht_get_read_status(void)
{
	return read_status;
}