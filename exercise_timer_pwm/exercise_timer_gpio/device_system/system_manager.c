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
  (v_sbutton->button).button_pin.io = (DRIVER_MCU_PORT_A << 4) | DRIVER_MCU_PIN_0;
  (v_sbutton->button).button_pin.mode = DRIVER_MCU_PIN_INPUT;
  (v_sbutton->button).button_pin.pull_type = DRIVER_MCU_PIN_NOPULL;
  (v_sbutton->button).button_type = DRIVER_BUTTON_TYPE_PD;
  system_button_init(v_sbutton);

  // Init Led
  (v_sled->ledR).led_pin.io = (DRIVER_MCU_PORT_D << 4) | DRIVER_MCU_PIN_12;
  (v_sled->ledR).led_pin.mode = DRIVER_MCU_PIN_AF_PP;
  (v_sled->ledR).led_pin.pull_type = DRIVER_MCU_PIN_NOPULL;
  (v_sled->ledR).led_pin.speed = DRIVER_MCU_PIN_VERY_HIGH;
  (v_sled->ledR).led_pin.af = DRIVER_MCU_PIN_AF2;
  (v_sled->ledR).led_type = DRIVER_LED_TYPE_KCOMMON;
  (v_sled->ledR).led_tim_channel = DRIVER_MCU_TIM_CHANNEL_1;

  (v_sled->ledG).led_pin.io = (DRIVER_MCU_PORT_D << 4) | DRIVER_MCU_PIN_13;
  (v_sled->ledG).led_pin.mode = DRIVER_MCU_PIN_AF_PP;
  (v_sled->ledG).led_pin.pull_type = DRIVER_MCU_PIN_NOPULL;
  (v_sled->ledG).led_pin.speed = DRIVER_MCU_PIN_VERY_HIGH;
  (v_sled->ledG).led_pin.af = DRIVER_MCU_PIN_AF2;
  (v_sled->ledG).led_type = DRIVER_LED_TYPE_KCOMMON;
  (v_sled->ledG).led_tim_channel = DRIVER_MCU_TIM_CHANNEL_2;

  (v_sled->ledB).led_pin.io = (DRIVER_MCU_PORT_D << 4) | DRIVER_MCU_PIN_14;
  (v_sled->ledB).led_pin.mode = DRIVER_MCU_PIN_AF_PP;
  (v_sled->ledB).led_pin.pull_type = DRIVER_MCU_PIN_NOPULL;
  (v_sled->ledB).led_pin.speed = DRIVER_MCU_PIN_VERY_HIGH;
  (v_sled->ledB).led_pin.af = DRIVER_MCU_PIN_AF2;
  (v_sled->ledB).led_type = DRIVER_LED_TYPE_KCOMMON;
  (v_sled->ledB).led_tim_channel = DRIVER_MCU_TIM_CHANNEL_3;
  system_led_init(v_sled, v_dmcu);
}

void system_manager_loop(system_button_t* v_sbutton, system_led_t* v_sled, driver_mcu_t* v_dmcu)
{
  // State transitions and outputs
  system_button_state_t v_sbutton_state;
  v_sbutton_state = system_button_read(v_sbutton);
  switch (currentState)
  {
  case SYSTEM_STATE_IDLE:
    if (v_sbutton_state == SYSTEM_BUTTON_1CLICK)
    {
      currentState = SYSTEM_STATE_LED1;
    }
    break;
  case SYSTEM_STATE_LED1:
    system_led_set(v_sled, v_dmcu, SYSTEM_LED_EVENT_ORANGE);
    if (v_sbutton_state == SYSTEM_BUTTON_2CLICK)
    {
      currentState = SYSTEM_STATE_LED2;
    }
    else if (v_sbutton_state == SYSTEM_BUTTON_HOLD)
    {
      currentState = SYSTEM_STATE_HOLD;
    }
    break;
  case SYSTEM_STATE_LED2:
    system_led_set(v_sled, v_dmcu, SYSTEM_LED_EVENT_VIOLET);
    if (v_sbutton_state == SYSTEM_BUTTON_2CLICK)
    {
      currentState = SYSTEM_STATE_LED3;
    }
    else if (v_sbutton_state == SYSTEM_BUTTON_HOLD)
    {
      currentState = SYSTEM_STATE_HOLD;
    }
    break;
  case SYSTEM_STATE_LED3:
    system_led_set(v_sled, v_dmcu, SYSTEM_LED_EVENT_AQUA);
    if (v_sbutton_state == SYSTEM_BUTTON_2CLICK)
    {
      currentState = SYSTEM_STATE_LED1;
    }
    else if (v_sbutton_state == SYSTEM_BUTTON_HOLD)
    {
      currentState = SYSTEM_STATE_HOLD;
    }
    break;
  case SYSTEM_STATE_HOLD:
    system_led_set(v_sled, v_dmcu, SYSTEM_LED_EVENT_OFF);
    if (v_sbutton_state == SYSTEM_BUTTON_RELEASE)
    {
      currentState = SYSTEM_STATE_IDLE;
    }
    break;
    // Handle additional states and transitions as needed
  }
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
