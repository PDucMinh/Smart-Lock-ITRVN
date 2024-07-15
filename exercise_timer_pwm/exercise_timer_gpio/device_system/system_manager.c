/**
 * @file       SYSTEM_MANAGER.c
 * @copyright
 * @license
 * @version    1.0
 * @date       2024-07-07
 * @author     Phat Nguyen Tan
 * @author
 *
 * @brief      <This file contains function definitions for system layer>
 *
 * @note
 * @example
 *
 * @example
 *
 */

/* Includes ----------------------------------------------------------- */
#include "system_manager.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static system_state_t currentState = SYSTEM_STATE_IDLE;
/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
void system_manager_init(system_button_t* v_sbutton, system_led_t* v_sled, driver_mcu_t* v_dmcu)
{
  // Init MCU
  driver_mcu_init(v_dmcu);

  // Init Button
  system_button_init(v_sbutton);

  // Init Led
  system_led_init(v_sled, v_dmcu);
}

void system_manager_loop(system_button_t* v_sbutton, system_led_t* v_sled, driver_mcu_t* v_dmcu)
{
  // State transitions and outputs
  switch (currentState)
  {
  case SYSTEM_STATE_IDLE:
    if (system_button_read(&(v_sbutton->button)) == SYSTEM_BUTTON_1CLICK)
    {
      currentState = SYSTEM_STATE_LED1;
    }
    break;
  case SYSTEM_STATE_LED1:
    system_led_set(v_sled, v_dmcu, SYSTEM_LED_EVENT_LED1);
    if (system_button_read(&(v_sbutton->button)) == SYSTEM_BUTTON_2CLICK)
    {
      currentState = SYSTEM_STATE_LED2;
    }
    else if (system_button_read(&(v_sbutton->button)) == SYSTEM_BUTTON_HOLD)
    {
      currentState = SYSTEM_STATE_HOLD;
    }
    break;
  case SYSTEM_STATE_LED2:
    system_led_set(v_sled, v_dmcu, SYSTEM_LED_EVENT_LED2);
    if (system_button_read(&(v_sbutton->button)) == SYSTEM_BUTTON_2CLICK)
    {
      currentState = SYSTEM_STATE_LED3;
    }
    else if (system_button_read(&(v_sbutton->button)) == SYSTEM_BUTTON_HOLD)
    {
      currentState = SYSTEM_STATE_HOLD;
    }
    break;
  case SYSTEM_STATE_LED3:
    system_led_set(v_sled, v_dmcu, SYSTEM_LED_EVENT_LED3);
    if (system_button_read(&(v_sbutton->button)) == SYSTEM_BUTTON_2CLICK)
    {
      currentState = SYSTEM_STATE_LED1;
    }
    else if (system_button_read(&(v_sbutton->button)) == SYSTEM_BUTTON_HOLD)
    {
      currentState = SYSTEM_STATE_HOLD;
    }
    break;
  case SYSTEM_STATE_HOLD:
    system_led_set(v_sled, v_dmcu, SYSTEM_LED_EVENT_OFF);
    if (system_button_read(&(v_sbutton->button)) == SYSTEM_BUTTON_RELEASE)
    {
      currentState = SYSTEM_STATE_IDLE;
    }
    break;
    // Handle additional states and transitions as needed
  }
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
