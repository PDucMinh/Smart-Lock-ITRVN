/**
 * @file       system_button.c
 * @copyright  Copyright (C) 2024. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    major.minor.patch
 * @date       2024-07-07
 * @author     Minh Pham Duc
 *
 * @brief      <A brief description of the content of the file>
 *
 * @note
 * @example
 */

/* Includes ----------------------------------------------------------- */
#include "system_button.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
void system_button_init(system_button_t *v_sbutton)
{
  DRIVER_CHECK_NULL(v_sbutton, DRIVER_STATE_FAIL);
  v_sbutton->button_state = SYSTEM_BUTTON_IDLE;
  v_sbutton->button_timeout = 0;
  v_sbutton->button_time = 0;
  v_sbutton->button_process = SYSTEM_BUTTON_PROCESS_INIT;
  driver_button_init(&(v_sbutton->button));
  v_sbutton->active = 1;
}

system_button_state_t system_button_read(system_button_t *v_sbutton)
{
  DRIVER_CHECK_NULL(v_sbutton, DRIVER_STATE_FAIL);
  DRIVER_CHECK_NULL(v_sbutton->active, DRIVER_STATE_FAIL);
  system_button_state_t button_state_ret;
  button_state_ret = v_sbutton->button_state;
  v_sbutton->button_state = SYSTEM_BUTTON_IDLE;
  return button_state_ret;
}

driver_button_state_t v_dbutton_state;
void system_button_loop(system_button_t *v_sbutton)
{
  DRIVER_CHECK_NULL(v_sbutton, DRIVER_STATE_FAIL);
  DRIVER_CHECK_NULL(v_sbutton->active, DRIVER_STATE_FAIL);
  v_dbutton_state = driver_button_read(&(v_sbutton->button));
  switch (v_sbutton->button_process)
  {
  case SYSTEM_BUTTON_PROCESS_INIT:
    if ((driver_button_read(&(v_sbutton->button)) == DRIVER_BUTTON_STATE_IS_PUSHED))
    {
      v_sbutton->button_time = 500;
      v_sbutton->button_process = SYSTEM_BUTTON_PROCESS_ON_1CLICK;
    }
    break;
  case SYSTEM_BUTTON_PROCESS_ON_1CLICK:
    if ((driver_button_read(&(v_sbutton->button)) == DRIVER_BUTTON_STATE_IS_PUSHED) && (v_sbutton->button_timeout))
    {
      v_sbutton->button_timeout = 0;
      v_sbutton->button_process = SYSTEM_BUTTON_PROCESS_ON_HOLD;
      v_sbutton->button_time = 2500;
    }
    else if (driver_button_read(&(v_sbutton->button)) == DRIVER_BUTTON_STATE_NO_PUSHED)
    {
      v_sbutton->button_process = SYSTEM_BUTTON_PROCESS_OFF_1CLICK;
      v_sbutton->button_time = 300;
    }
    break;
  case SYSTEM_BUTTON_PROCESS_OFF_1CLICK:
    if ((driver_button_read(&(v_sbutton->button)) == DRIVER_BUTTON_STATE_NO_PUSHED) && (v_sbutton->button_timeout))
    {
      v_sbutton->button_timeout = 0;
      v_sbutton->button_process = SYSTEM_BUTTON_PROCESS_INIT;
      v_sbutton->button_state = SYSTEM_BUTTON_1CLICK;
    }
    else if (driver_button_read(&(v_sbutton->button)) == DRIVER_BUTTON_STATE_IS_PUSHED)
    {
      v_sbutton->button_process = SYSTEM_BUTTON_PROCESS_ON_2CLICK;
      v_sbutton->button_time = 500;
    }
    break;
  case SYSTEM_BUTTON_PROCESS_ON_2CLICK:
    if ((driver_button_read(&(v_sbutton->button)) == DRIVER_BUTTON_STATE_IS_PUSHED) && (v_sbutton->button_timeout))
    {
      v_sbutton->button_timeout = 0;
      v_sbutton->button_process = SYSTEM_BUTTON_PROCESS_INIT;
    }
    else if (driver_button_read(&(v_sbutton->button)) == DRIVER_BUTTON_STATE_NO_PUSHED)
    {
      v_sbutton->button_time = 300;
      v_sbutton->button_process = SYSTEM_BUTTON_PROCESS_OFF_2CLICK;
    }
    break;
  case SYSTEM_BUTTON_PROCESS_OFF_2CLICK:
    if ((driver_button_read(&(v_sbutton->button)) == DRIVER_BUTTON_STATE_NO_PUSHED) && (v_sbutton->button_timeout))
    {
      v_sbutton->button_timeout = 0;
      v_sbutton->button_process = SYSTEM_BUTTON_PROCESS_INIT;
      v_sbutton->button_state = SYSTEM_BUTTON_2CLICK;
    }
    else if (driver_button_read(&(v_sbutton->button)) == DRIVER_BUTTON_STATE_IS_PUSHED)
    {
      v_sbutton->button_time = 0;
      v_sbutton->button_timeout = 0;
      v_sbutton->button_process = SYSTEM_BUTTON_PROCESS_INIT;
    }
    break;
  case SYSTEM_BUTTON_PROCESS_ON_HOLD:
    if ((driver_button_read(&(v_sbutton->button)) == DRIVER_BUTTON_STATE_IS_PUSHED) && (v_sbutton->button_timeout))
    {
      v_sbutton->button_timeout = 0;
      v_sbutton->button_state = SYSTEM_BUTTON_HOLD;
      v_sbutton->button_process = SYSTEM_BUTTON_PROCESS_WAIT_RELEASE;
      v_sbutton->button_time = 2000;
    }
    else if (driver_button_read(&(v_sbutton->button)) == DRIVER_BUTTON_STATE_NO_PUSHED)
    {
      v_sbutton->button_time = 0;
      v_sbutton->button_timeout = 0;
      v_sbutton->button_process = SYSTEM_BUTTON_PROCESS_INIT;
    }
    break;
  case SYSTEM_BUTTON_PROCESS_WAIT_RELEASE:
    if ((driver_button_read(&(v_sbutton->button)) == DRIVER_BUTTON_STATE_IS_PUSHED) && (v_sbutton->button_timeout))
    {
      v_sbutton->button_timeout = 0;
      v_sbutton->button_process = SYSTEM_BUTTON_PROCESS_FAULT;
    }
    else if (driver_button_read(&(v_sbutton->button)) == DRIVER_BUTTON_STATE_NO_PUSHED)
    {
      v_sbutton->button_time = 300;
      v_sbutton->button_process = SYSTEM_BUTTON_PROCESS_OFF_RELEASE;
    }
    break;
  case SYSTEM_BUTTON_PROCESS_OFF_RELEASE:
    if ((driver_button_read(&(v_sbutton->button)) == DRIVER_BUTTON_STATE_NO_PUSHED) && (v_sbutton->button_timeout))
    {
      v_sbutton->button_timeout = 0;
      v_sbutton->button_process = SYSTEM_BUTTON_PROCESS_INIT;
      v_sbutton->button_state = SYSTEM_BUTTON_RELEASE;
    }
    else if (driver_button_read(&(v_sbutton->button)) == DRIVER_BUTTON_STATE_IS_PUSHED)
    {
      v_sbutton->button_time = 0;
      v_sbutton->button_timeout = 0;
      v_sbutton->button_process = SYSTEM_BUTTON_PROCESS_FAULT;
    }
    break;
  default:
    if (driver_button_read(&(v_sbutton->button)) == DRIVER_BUTTON_STATE_NO_PUSHED)
    {
      v_sbutton->button_process = SYSTEM_BUTTON_PROCESS_OFF_RELEASE;
      v_sbutton->button_time = 300;
    }
    break;
  }
}

void system_button_timeout(system_button_t *v_sbutton)
{
  if (v_sbutton->button_time > 0)
  {
    v_sbutton->button_time--;
    if (v_sbutton->button_time == 0)
    {
      v_sbutton->button_timeout = 1;
    }
  }
}
/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
