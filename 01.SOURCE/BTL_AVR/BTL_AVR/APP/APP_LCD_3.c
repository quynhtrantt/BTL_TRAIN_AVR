#include "APP_LCD_3.h"
#include "APP_BUTTON.h"
#include "BSP_BUTTON.h"
#include "DATA_BUTTON.h"
#include "BSP_TIMER.h"
#include "BSP_LCD.h"

uint8_t set_temp = 16;
extern uint16_t	app_button_timer_count;
typedef enum
{
    STATE_IDLE,
    STATE_WAIT_HOLD,
    STATE_AUTO_REPEAT,
} temp_control_state_t;

static uint8_t temp_state;


void app_LCD_3_update()
{
    
    switch (temp_state)
    {
    case STATE_IDLE:
        if(GPIO_readPin(2, 0) == BUTTON_PRESSED)
        {
            if(set_temp < 30)
            {
                set_temp++;
            }
            else
            {
                break;
            }
            LCD_WriteBus4(set_temp);
            app_button_timer_count = 1000;
        }
        else if(GPIO_readPin(2, 1) == BUTTON_PRESSED)
        {
            if(set_temp > 16)
            {
                set_temp--;
            }
            else
            {
                break;
            }
            LCD_WriteBus4(set_temp);
            app_button_timer_count = 1000;
        }
        else 
        {
            LCD_WriteBus4(set_temp);
        }
        break;
    case STATE_WAIT_HOLD:
        if(GPIO_readPin(2, 0) == BUTTON_RELEASED || GPIO_readPin(2, 1) == BUTTON_RELEASED)
        {
            temp_state = STATE_IDLE;
            app_button_timer_count = 0; // timer oft
        }
        else if(0 == app_button_timer_count) // timer expired
        {
            temp_state = STATE_AUTO_REPEAT;
        }
        break;
    case STATE_AUTO_REPEAT:
        if(GPIO_readPin(2, 0) == BUTTON_PRESSED)
        {
            app_button_timer_count = 100;
            while( 0 == app_button_timer_count)
            {
                set_temp++;
                LCD_WriteBus4(set_temp);
                
            }
        }
        else if(GPIO_readPin(2, 1) == BUTTON_PRESSED)
        {
            app_button_timer_count = 100;
            while( 0 == app_button_timer_count)
            {
                set_temp--;
                LCD_WriteBus4(set_temp);
                
            }
        }
        else 
        {
            temp_state = STATE_IDLE;
            app_button_timer_count = 0;
        }

        break;
    }
} 