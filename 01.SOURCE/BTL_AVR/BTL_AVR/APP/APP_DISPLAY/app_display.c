#include "app_display.h"
#include "BSP_LCD.h"
#include "stdint.h"
#include "stdio.h"
#include "BSP_TIMER.h"
#include "APP_LCD_3.h"
#include "APP_BUTTON.h"


static uint8_t current_page = PAGE_TEMPERATURE;
static uint8_t temperature = TEMPERATURE;
static uint8_t humidity = PAGE_HUMIDITY;
static uint16_t press_count = PAGE_COUNT;
extern uint8_t set_temp ;
void App_Display_Init(void)
{
	BSP_LCD_Init();
	App_Display_ShowPage(current_page);
}

void App_Display_ShowPage(uint8_t page)
{
	char buffer[17];

	current_page = page;

	LCD_Clear();

	switch (current_page)
	{
		case PAGE_TEMPERATURE:
		LCD_GotoXY(0U, 0U);
		LCD_PutString("  TEMPERATURE");

		sprintf(buffer, "      %02u C", temperature);
		LCD_GotoXY(0U, 1U);
		LCD_PutString(buffer);
		break;

		case PAGE_HUMIDITY:
		LCD_GotoXY(0U, 0U);
		LCD_PutString("    HUMIDITY");

		sprintf(buffer, "      %02u %%", humidity);
		LCD_GotoXY(0U, 1U);
		LCD_PutString(buffer);
		break;

		case PAGE_COUNT:
		LCD_GotoXY(0U, 0U);
		LCD_PutString("  SET TEMP ");

		sprintf(buffer, "      %u", set_temp);
		LCD_GotoXY(0U, 1U);
		LCD_PutString(buffer);
		break;

		default:
		current_page = PAGE_TEMPERATURE;

		LCD_GotoXY(0U, 0U);
		LCD_PutString("  TEMPERATURE");

		sprintf(buffer, "      %02u C", temperature);
		LCD_GotoXY(0U, 1U);
		LCD_PutString(buffer);
		break;
	}
}

void App_Display_NextPage(void)
{
	current_page++;

	if (current_page > PAGE_COUNT)
	{
		current_page = PAGE_TEMPERATURE;
	}

	App_Display_ShowPage(current_page);
}

void App_Display_SetTemperature(uint8_t temperature_value)
{
	if (temperature != temperature_value)
	{
		temperature = temperature_value;

		if (current_page == PAGE_TEMPERATURE)
		{
			App_Display_ShowPage(current_page);
		}
	}
}

void App_Display_SetHumidity(uint8_t humidity_value)
{
	if (humidity != humidity_value)
	{
		humidity = humidity_value;

		if (current_page == PAGE_HUMIDITY)
		{
			App_Display_ShowPage(current_page);
		}
	}
}

void App_Display_SetCount(uint16_t count)
{
	if (press_count != count)
	{
		press_count = count;

		if (current_page == PAGE_COUNT)
		{
			App_Display_ShowPage(current_page);
		}
	}
}