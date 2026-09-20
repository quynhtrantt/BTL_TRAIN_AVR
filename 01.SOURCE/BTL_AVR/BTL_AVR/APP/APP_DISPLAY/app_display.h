#ifndef APP_DISPLAY_H_
#define APP_DISPLAY_H_
#include "LCD.h"
#include "app_button.h"
#include ""

#define PAGE_TEMPERATURE
#define TEMPERATURE
#define 


void App_Display_Init(void)
void App_Display_ShowPage(uint8_t page)
void App_Display_NextPage(void)  
void App_Display_SetTemperature(uint8_t temperature_value)
void App_Display_SetHumidity(uint8_t humidity_value)
void App_Display_SetCount(uint16_t count)


#endif 