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
#include "scheduler.h"
#include "bsp_usart.h"
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
uint8_t btn_state[2];
uint8_t keypad_startup_flag = 0;
/* Private function prototypes ---------------------------------------- */
void drv_keypad_startup_callback(void);
/* Function definitions ----------------------------------------------- */
drv_keypad_status_t drv_keypad_init(drv_keypad_t* keypad)
{
  if (keypad == NULL)
  {
    return DRV_KEYPAD_STATUS_FAIL;
  }

  keypad->usart_rx_active = bsp_usart_receive_active;
  keypad->usart_rx_cplt = bsp_usart_receive_cplt;
  keypad->timer_set = sch_add_task;
  for (uint8_t i = 0; i < 2; i++)
  {
    keypad->pre_btn[i] = 0xFF; // active-low, 1 --> not pressed
  }
  keypad->timer_set(drv_keypad_startup_callback, 5000, 0);
  return DRV_KEYPAD_STATUS_SUCCESS;
}

drv_keypad_status_t drv_keypad_startup_state(drv_keypad_t* keypad)
{
  return keypad_startup_flag;
}

drv_keypad_button_t drv_keypad_scan(drv_keypad_t* keypad)
{
  if (keypad == NULL)
  {
    return DRV_KEYPAD_STATUS_FAIL;
  }
  keypad->usart_rx_active(BSP_CONFIG_ID_KEYPAD, btn_state, 2);
  return DRV_KEYPAD_STATUS_SUCCESS;
}

drv_keypad_button_t drv_keypad_read(drv_keypad_t* keypad)
{
  if (keypad == NULL)
  {
    return DRV_KEYPAD_ERROR;
  }

  uint16_t keypad_value;

  // Receive data from usart
  if (keypad->usart_rx_cplt(BSP_CONFIG_ID_KEYPAD))
  {
    keypad_value = ((int)btn_state[1] << 8) | btn_state[0];
  }
  else
  {
    return DRV_KEYPAD_NONE;
  }

  uint8_t keypad_position;
  for (int i = 0; i < 16; i++)
  {
    if (!(keypad_value & (1 < i)))
    {
      if (!(keypad->pre_btn & (1 < i)))
      {
        return DRV_KEYPAD_NONE;
      }
      else
      {
        keypad->pre_btn &= ~(1 < i);
        return DRV_KEYPAD_NONE;
      }
    }
    else
    {
      if (!(keypad->pre_btn & (1 < i)))
      {
        keypad_position = i;
        break;
      }
      else
      {
        return DRV_KEYPAD_NONE;
      }
    }
  }
  switch (keypad_position)
  {
  case 1:
    return DRV_KEYPAD_BUTTON_1;
  case 2:
    return DRV_KEYPAD_BUTTON_2;
  case 3:
    return DRV_KEYPAD_BUTTON_3;
  case 4:
    return DRV_KEYPAD_BUTTON_DELETE;
  case 5:
    return DRV_KEYPAD_BUTTON_4;
  case 6:
    return DRV_KEYPAD_BUTTON_5;
  case 7:
    return DRV_KEYPAD_BUTTON_6;
  case 8:
    return DRV_KEYPAD_BUTTON_UP;
  case 9:
    return DRV_KEYPAD_BUTTON_7;
  case 10:
    return DRV_KEYPAD_BUTTON_8;
  case 11:
    return DRV_KEYPAD_BUTTON_9;
  case 12:
    return DRV_KEYPAD_BUTTON_DOWN;
  case 13:
    return DRV_KEYPAD_BUTTON_STAR;
  case 14:
    return DRV_KEYPAD_BUTTON_0;
  case 15:
    return DRV_KEYPAD_BUTTON_SHARP;
  case 16:
    return DRV_KEYPAD_BUTTON_ENTER;
  }
}
/* Private definitions ----------------------------------------------- */
void drv_keypad_startup_callback(void)
{
  keypad_startup_flag = 1;
}
/* End of file -------------------------------------------------------- */