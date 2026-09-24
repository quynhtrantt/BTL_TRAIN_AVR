/*
 * BSP_BUTTON.h
 *
 * Created: 9/16/2026 4:07:37 PM
 *  Author: HP
 */ 


#ifndef BSP_BUTTON_H_
#define BSP_BUTTON_H_

#include <stdint.h>


#define BUTTON_PRESSED   0u
#define BUTTON_RELEASED  1u

void    bsp_button_init();
uint8_t bsp_button_start_get_state(void);
uint8_t bsp_button_page_get_state(void);

#endif /* BSP_BUTTON_H_ */