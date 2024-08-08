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

/*
  --------------------
  |1 | 2 | 3 | delete|
  --------------------
  |4 | 5 | 6 |  up   |
  --------------------
  |7 | 8 | 9 | down  |
  --------------------
  |* | 0 | # | enter |
  --------------------
*/

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
  for (uint8_t i = 0; i < 16; i++) 
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
  uint8_t btn_pressed_position = 20;

  // Receive data from usart
  if (keypad->usart_rx(BSP_CONFIG_KEYPAD, rx_data, 2) == 1) //  1 --> receive successed
  {
    key_value = (rx_data[0] << 8) | rx_data[1];

    for (uint8_t i = 0; i < 16; i++) 
    {
      if (key_value & (1 << i)) 
      {
        buttons_pressed[i] = 1;

        // Count the number of button pressed and returned the location
        count_buttons_pressed = count_buttons_pressed + 1;
        btn_pressed_position = i + 1;
      }
    }
  } 
  else                                                      //  0 --> receive failed
  {
    return DRV_KEYPAD_ERROR;
  }


  // Only 1 button is allowed per time point
  if ((count_buttons_pressed = 0) || (count_buttons_pressed > 1))
  {
    // Reset state of all buttons when keypad were released
    for (uint8_t i = 0; i < 16; i++) 
    {
      keypad->pre_btn[i] = 1; // active-low, 1 --> not pressed
    }
    return DRV_KEYPAD_ERROR;
  }


  // Check if button was received before
  // If button is held, it will receive 1 time
  if (keypad->pre_btn[btn_pressed_position - 1] == 0)
  {
    return DRV_KEYPAD_ERROR;
  }
  else
  {
    keypad->pre_btn[btn_pressed_position - 1] = 0; // active-low, 0 --> pressed
    switch (btn_pressed_position)
    {
    case 1:
      return DRV_KEYPAD_BUTTON_1;
      break;
    case 2:
      return DRV_KEYPAD_BUTTON_2;
      break;
    case 3:
      return DRV_KEYPAD_BUTTON_3;
      break;
    case 4:
      return DRV_KEYPAD_BUTTON_DELETE;
      break;
    case 5:
      return DRV_KEYPAD_BUTTON_4;
      break;
    case 6:
      return DRV_KEYPAD_BUTTON_5;
      break;
    case 7:
      return DRV_KEYPAD_BUTTON_6;
      break;
    case 8:
      return DRV_KEYPAD_BUTTON_UP;
      break;
    case 9:
      return DRV_KEYPAD_BUTTON_7;
      break;
    case 10:
      return DRV_KEYPAD_BUTTON_8;
      break;
    case 11:
      return DRV_KEYPAD_BUTTON_9;
      break;
    case 12:
      return DRV_KEYPAD_BUTTON_DOWN;
      break;
    case 13:
      return DRV_KEYPAD_BUTTON_STAR;
      break;
    case 14:
      return DRV_KEYPAD_BUTTON_0;
      break;
    case 15:
      return DRV_KEYPAD_BUTTON_SHARP;
      break;
    case 16:
      return DRV_KEYPAD_BUTTON_ENTER;
      break;
    default:
      return DRV_KEYPAD_ERROR;
      break;
    }
  }
}
/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */