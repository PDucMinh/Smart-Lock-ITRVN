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


/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */