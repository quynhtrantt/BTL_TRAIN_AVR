#include "avr/io.h"
#include "BSP_LCD.h"
#include "bsp_button.h"
#include "app_display.h"

// ??nh ngh?a ID cho 2 nút (ho?c b? vào file board.h c?a b?n)
#define BTN_PAGE_ID  0
#define BTN_COUNT_ID 1

int main(void)
{
	// 1. Kh?i t?o ngo?i vi & ?ng d?ng
	BSP_LCD_Init();
	BSP_Button_Init();
	App_Display_Init();
	
	uint16_t my_count = 0; // Bi?n l?u s? l?n ??m

	// 2. Vòng l?p chính
	while (1)
	{
		// --- X? lý nút chuy?n trang ---
		if (BSP_Button_IsPressed(BTN_PAGE_ID))
		{
			App_Display_NextPage();
		}

		// --- X? lý nút ??m s? ---
		if (BSP_Button_IsPressed(BTN_COUNT_ID))
		{
			my_count++;
			// ??y giá tr? m?i sang LCD (LCD s? t? bi?t có c?n v? l?i hay không)
			App_Display_SetCount(my_count);
		}
	}
	
	return 0;
}