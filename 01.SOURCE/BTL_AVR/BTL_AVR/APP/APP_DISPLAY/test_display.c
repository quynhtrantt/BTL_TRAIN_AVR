#include "avr/io.h"
#include "BSP_LCD.h"
#include "bsp_button.h"
#include "app_display.h"

#define BUTTON_PAGE_ID  0
#define BUTTON_COUNT_ID 1

int main(void)
{
	BSP_LCD_Init();
	BSP_Button_Init();
	App_Display_Init();
	
	uint16_t my_count = 0; 

	while (1)
	{
		if (BSP_Button_IsPressed(BUTTON_PAGE_ID))
		{
			App_Display_NextPage();
		}

		if (BSP_Button_IsPressed(BUTTON_COUNT_ID))
		{
			my_count++;

			App_Display_SetCount(my_count);
		}
	}
	
	return 0;
}