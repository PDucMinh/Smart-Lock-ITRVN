/**
 * @file       SYSTEM_BUTTON.c
 * @copyright  Copyright (C) 2024. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    major.minor.patch
 * @date       2024-07-07
 * @author     Minh Pham Duc
 *
 * @brief      <A brief description of the content of the file>
 *
 * @note
 * @example    example_file_1.c
 *             Example_1 description
 * @example    example_file_2.c
 *             Example_2 description
 */

/* Includes ----------------------------------------------------------- */
#include "SYSTEM_BUTTON.h"
#include "DRIVER_BUTTON.h"

/* Private defines ---------------------------------------------------- */
#define PRIVATE_DEFINE_1 (0) /*!< Description of PRIVATE_DEFINE_1 */
#define PRIVATE_DEFINE_2 (0) /*!< Description of PRIVATE_DEFINE_2 */
/* Private enumerate/structure ---------------------------------------- */
typedef enum
{
  STATE_CLICK,
  STATE_OFF,
  STATE_INIT
} button_state_process_t;
/* Private macros ----------------------------------------------------- */
/**
 * @brief  <macro description>
 *
 * @param[in]     <param_name>  <param_despcription>
 * @param[out]    <param_name>  <param_despcription>
 * @param[inout]  <param_name>  <param_despcription>
 *
 * @attention  <API attention note>
 *
 * @return
 *  - 0: Success
 *  - 1: Error
 */
#define PRIVATE_MACRO(a) do_something_with(a)

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
int system_button_timer;
char system_button_timeout;
int click;
button_state_process_t button_process;
system_button_t *v_sbutton_1;
/* Private function prototypes ---------------------------------------- */
void system_button_timer_run();
char system_button_time_out();
void set_timer(int time);
void system_button_set_state(driver_button_t* db, driver_state_t *errorCode);
/* Function definitions ----------------------------------------------- */
void system_button_init(system_button_t *v_sbutton)
{
  click = 0;
  system_button_timeout = 0;
  button_process = STATE_INIT;
  system_button_timer = 0;
  v_sbutton_1 = v_sbutton;
}

system_button_state_t system_button_read(driver_button_t* db)
{
  if (click == 1)
  {
    return SYSTEM_BUTTON_1CLICK;
  }
  if (click == 2)
  {
    return SYSTEM_BUTTON_2CLICK;
  }
  if (click > 2)
  {
    return SYSTEM_BUTTON_HOLD;
  }
  return SYSTEM_BUTTON_RELEASE;
}

void system_button_loop(driver_button_t *db, driver_state_t *errorCode)
{
  timer_run();
  system_button_set_state(db, errorCode);
}

/* Private definitions ----------------------------------------------- */
void timer_run()
{
  if (system_button_timer > 0)
  {
    system_button_timer--;
    if (system_button_timer <= 0)
    {
      system_button_timeout = 1;
    }
  }
}

void system_button_set_state(driver_button_t* db, driver_state_t *errorCode)
{
  switch (button_process)
  {
  case STATE_CLICK:
    if ((driver_button_read(db, errorCode) == DRIVER_BUTTON_IS_PUSHED) && (time_out()))
    {
      click++;
      set_timer(500);
    }
    if (driver_button_read(db, errorCode) == DRIVER_BUTTON_NO_PUSHED)
    {
      set_timer(300);
      button_process = STATE_OFF;
    }
    break;
  case STATE_OFF:
    if ((driver_button_read(db, errorCode) == DRIVER_BUTTON_NO_PUSHED) && (time_out()))
    {
      click = 0;
      button_process = STATE_INIT;
    }
    if (driver_button_read(db, errorCode) == DRIVER_BUTTON_IS_PUSHED)
    {
      click++;
      set_timer(500);
      button_process = STATE_CLICK;
    }
    break;
  case STATE_INIT:
    if (driver_button_read(db, errorCode) == DRIVER_BUTTON_IS_PUSHED)
    {
      click++;
      set_timer(500);
      button_process = STATE_CLICK;
    }
    break;
  default:
    button_process = STATE_INIT;
    break;
  }
}

char time_out()
{
  if (system_button_timeout)
  {
    system_button_timeout = 0;
    return 1;
  }
  return 0;
}

void set_timer(int time)
{
  system_button_timer = time;
  system_button_timeout = 0;
}
/* End of file -------------------------------------------------------- */
