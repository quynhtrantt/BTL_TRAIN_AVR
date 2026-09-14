#include "LCD.h"

#define LCD_PRT PORTA
#define LCD_DDR DDRA
#define LCD_RS  PA0
#define LCD_EN  PA1
#define LCD_D4  PA4
#define LCD_D5  PA5
#define LCD_D6  PA6
#define LCD_D7  PA7

#define LCD_RS_HIGH() (LCD_PORT |= (1 << LCD_RS_PIN))
#define LCD_RS_LOW()  (LCD_PORT &= ~(1 << LCD_RS_PIN))
#define LCD_EN_HIGH() (LCD_PORT |= (1 << LCD_EN_PIN))
#define LCD_EN_LOW()  (LCD_PORT &= ~(1 << LCD_EN_PIN))

int main(void)
{
	LCD_Init();
	LCD_PutString("qiqi");
	
    while (1) 
    {
    }
}

