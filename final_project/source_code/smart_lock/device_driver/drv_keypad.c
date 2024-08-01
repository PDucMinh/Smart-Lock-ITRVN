/**
 * @file       drv_keypad.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       2024-08-01
 * @author     Phat Nguyen Tan
 * @author
 *
 * @brief      <This file is source code file to define functions for TTP229 keypad module>
 *
 * @note
 */

/* Includes ----------------------------------------------------------- */
#include "drv_keypad.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
drv_keypad_status_t drv_keypad_init(drv_keypad_t *keypad)
{
  if (keypad == NULL)
  {
    return DRV_KEYPAD_STATUS_FAIL;
  }

  keypad->usart_rx = bsp_usart_rx;
  for (int i = 0; i < 16; i++) 
  {
    keypad->pre_btn[i] = 1; // active-low, 1 --> not pressed
  }

  return DRV_KEYPAD_STATUS_SUCCESS;
}

drv_keypad_button_t drv_keypad_read(drv_keypad_t *keypad)
{
  if (keypad == NULL)
  {
    return DRV_KEYPAD_ERROR;
  }

  uint8_t rx_data[2];
  uint16_t key_value;
  uint8_t buttons_pressed[16] = {0};
  uint8_t count_buttons_pressed = 0;

  // Receive data from usart
  if (keypad->usart_rx(BSP_CONFIG_KEYPAD, rx_data, 2) == 1) //  1 --> receive successed
  {
    key_value = (rx_data[0] << 8) | rx_data[1];

    for (uint8_t i = 0; i < 16; i++) 
    {
      if (key_value & (1 << i)) 
      {
        buttons_pressed[i] = 1;
      }
    }
  } 
  else 
  {
    return DRV_KEYPAD_ERROR;
  }
  
  for (uint8_t i = 0; i < 16; i++) 
  {
    if (buttons_pressed[i] == 1) 
    {
      count_buttons_pressed = count_buttons_pressed + 1;
    }
  }

  if (count_buttons_pressed = 0)
  {
    return DRV_KEYPAD_ERROR;
  }
  else if (count_buttons_pressed > 1)
  {
    return DRV_KEYPAD_ERROR;
  }
  else
  {
    
  }



}
/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */