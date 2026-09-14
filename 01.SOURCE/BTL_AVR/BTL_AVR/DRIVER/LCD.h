#ifndef LCD_H_
#define LCD_H_
#include "stdint.h"

void LCD_Init(void);
void LCD_Clear(void);
void LCD_Home(void);

void LCD_SendCommand(uint8_t cmd);
void LCD_SendData(uint8_t data);

void LCD_PutChar(char c);
void LCD_PutString(const char *s);
void LCD_GotoXY(uint8_t col, uint8_t row);

#endif
