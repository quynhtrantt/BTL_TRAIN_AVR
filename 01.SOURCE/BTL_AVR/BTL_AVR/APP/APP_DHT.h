#ifndef APP_DHT_H_
#define APP_DHT_H_

#include <stdint.h>

void app_dht_init(void);
void app_dht_update(void);

uint8_t app_dht_get_read_status(void);

#endif