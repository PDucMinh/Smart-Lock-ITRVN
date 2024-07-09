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
#include "SYSTEM_MANAGER.h"
#include "SYSTEM_BUTTON.h"
#include "DRIVER_BUTTON.h"
#include "DRIVER_MCU.h"
#include "DRIVER_LED.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */


/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
void system_manager_init(driver_button_t* db, driver_led_t* dl)
{
  // Init MCU
  driver_mcu_init();

  // Init Button
  db->button_type = DRIVER_BUTTON_PULL_DOWN;
  db->button_io = (DRIVER_MCU_PORT_A) | (DRIVER_MCU_PIN_0); // PA0
  driver_button_init(db);

  // Init Led
  dl->led_type = DRIVER_LED_KCOMMON;
  dl->led_io = (DRIVER_MCU_PORT_D) | (DRIVER_MCU_PIN_12); // PD12
  driver_led_init(dl);
  (dl + 1)->led_type = DRIVER_LED_KCOMMON;
  (dl + 1)->led_io = (DRIVER_MCU_PORT_D) | (DRIVER_MCU_PIN_13); // PD13
  driver_led_init(dl + 1);
  (dl + 2)->led_type = DRIVER_LED_KCOMMON;
  (dl + 2)->led_io = (DRIVER_MCU_PORT_D) | (DRIVER_MCU_PIN_14); // PD14
  driver_led_init(dl + 2);
}
system_button_state_t sys_man_st;
system_state_t currentState = SYSTEM_IDLE;
void system_manager_loop(driver_button_t* db, driver_led_t* dl)
{
  // Current state variable
  sys_man_st = system_button_read(db);
  // State transitions and outputs
  switch (currentState)
  {
  case SYSTEM_IDLE:
    if (system_button_read(db) == SYSTEM_BUTTON_1CLICK)
    {
//      currentState = SYSTEM_LED1_ON;
      driver_led_set(dl, DRIVER_LED_ON);
      driver_led_set(dl + 1, DRIVER_LED_OFF);
      driver_led_set(dl + 2, DRIVER_LED_OFF);
      if (system_button_read(db) == SYSTEM_BUTTON_RELEASE)
      {
      currentState = SYSTEM_LED1_ON;
      }
    }
    break;
  case SYSTEM_LED1_ON:
    if (system_button_read(db) == SYSTEM_BUTTON_2CLICK)
    {
      driver_led_set(dl, DRIVER_LED_OFF);
      driver_led_set(dl + 1, DRIVER_LED_ON);
      driver_led_set(dl + 2, DRIVER_LED_OFF);
      if (system_button_read(db) == SYSTEM_BUTTON_RELEASE)
      {
      currentState = SYSTEM_LED2_ON;
      }
    }
    else if (system_button_read(db) == SYSTEM_BUTTON_HOLD)
    {
      currentState = SYSTEM_HOLD;
      driver_led_set(dl, DRIVER_LED_OFF);
      driver_led_set(dl + 1, DRIVER_LED_OFF);
      driver_led_set(dl + 2, DRIVER_LED_OFF);
    }
    break;
  case SYSTEM_LED2_ON:
    if (system_button_read(db) == SYSTEM_BUTTON_2CLICK)
    {
//      currentState = SYSTEM_LED3_ON;
      driver_led_set(dl, DRIVER_LED_OFF);
      driver_led_set(dl + 1, DRIVER_LED_OFF);
      driver_led_set(dl + 2, DRIVER_LED_ON);
      if (system_button_read(db) == SYSTEM_BUTTON_RELEASE)
      {
      currentState = SYSTEM_LED3_ON;
      }
    }
    else if (system_button_read(db) == SYSTEM_BUTTON_HOLD)
    {
      currentState = SYSTEM_HOLD;
      driver_led_set(dl, DRIVER_LED_OFF);
      driver_led_set(dl + 1, DRIVER_LED_OFF);
      driver_led_set(dl + 2, DRIVER_LED_OFF);
    }
    break;
  case SYSTEM_LED3_ON:
    if (system_button_read(db) == SYSTEM_BUTTON_2CLICK)
    {
//      currentState = SYSTEM_LED1_ON;
      driver_led_set(dl, DRIVER_LED_ON);
      driver_led_set(dl + 1, DRIVER_LED_OFF);
      driver_led_set(dl + 2, DRIVER_LED_OFF);
      if (system_button_read(db) == SYSTEM_BUTTON_RELEASE)
      {
      currentState = SYSTEM_LED1_ON;
      }
    }
    else if (system_button_read(db) == SYSTEM_BUTTON_HOLD)
    {
      currentState = SYSTEM_HOLD;
      driver_led_set(dl, DRIVER_LED_OFF);
      driver_led_set(dl + 1, DRIVER_LED_OFF);
      driver_led_set(dl + 2, DRIVER_LED_OFF);
    }
    break;
  case SYSTEM_HOLD:
    if (system_button_read(db) == SYSTEM_BUTTON_RELEASE)
    {
      currentState = SYSTEM_IDLE;
    }
    break;
    // Handle additional states and transitions as needed
  }
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
