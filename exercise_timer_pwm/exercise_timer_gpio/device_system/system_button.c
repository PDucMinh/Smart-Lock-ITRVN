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
int v_sbutton_timer;
int v_sbutton_timer_2;
char v_sbutton_timeout;
char v_sbutton_timeout_2;
int v_sbutton_click;
button_state_process_t v_sbutton_process;
system_button_t *v_sbutton_1;
/* Private function prototypes ---------------------------------------- */
void system_button_timer_run();
char system_button_time_out();
void set_timer(int time);
void system_button_set_state(driver_button_t *db);
/* Function definitions ----------------------------------------------- */
void system_button_init(system_button_t *v_sbutton)
{
  v_sbutton_click = 0;
  v_sbutton_timeout = 0;
  v_sbutton_timer = 0;
  v_sbutton_timeout_2 = 0;
  v_sbutton_timer_2 = 0;
  v_sbutton_process = STATE_INIT;
  v_sbutton_1 = v_sbutton;
}

system_button_state_t system_button_read(system_button_t *v_button)
{
  if (v_sbutton_click == 1)
  {
    (*v_button).button_state = SYSTEM_BUTTON_1CLICK;
    return SYSTEM_BUTTON_1CLICK;
  }
  if (v_sbutton_click == 2)
  {
    (*v_button).button_state = SYSTEM_BUTTON_2CLICK;
    return SYSTEM_BUTTON_2CLICK;
  }
  if (v_sbutton_click > 2)
  {
    (*v_button).button_state = SYSTEM_BUTTON_HOLD;
    return SYSTEM_BUTTON_HOLD;
  }

  (*v_button).button_state = SYSTEM_BUTTON_RELEASE;
  return SYSTEM_BUTTON_RELEASE;
}

void system_button_loop(system_button_t *v_button)
{
  timer_run();
  system_button_set_state((*v_button).button);
}

/* Private definitions ----------------------------------------------- */
void timer_run()
{
  if (v_sbutton_timer > 0)
  {
    v_sbutton_timer--;
    if (v_sbutton_timer <= 0)
    {
      v_sbutton_timeout = 1;
    }
  }
  if ((v_sbutton_timer_2 > 0) && time_out_2())
  {
    v_sbutton_timer_2--;
    if (v_sbutton_timer_2 <= 0)
    {
      v_sbutton_timeout_2 = 1;
    }
  }
}

void system_button_set_state(driver_button_t *db)
{
  switch (v_sbutton_process)
  {
  case STATE_CLICK:
    if ((driver_button_read(db) == DRIVER_BUTTON_IS_PUSHED) && (time_out()))
    {
      v_sbutton_click++;
      set_timer(500);
    }
    if (driver_button_read(db) == DRIVER_BUTTON_NO_PUSHED)
    {
      set_timer(300);
      v_sbutton_process = STATE_OFF;
    }
    break;
  case STATE_OFF:
    set_timer_2(3000);
    if ((driver_button_read(db) == DRIVER_BUTTON_NO_PUSHED) && (time_out()))
    {
      v_sbutton_click = 0;
      v_sbutton_process = STATE_INIT;
    }
    if (driver_button_read(db) == DRIVER_BUTTON_IS_PUSHED)
    {
      v_sbutton_click++;
      set_timer(500);
      v_sbutton_process = STATE_CLICK;
    }
    break;
  case STATE_INIT:
    if (driver_button_read(db) == DRIVER_BUTTON_IS_PUSHED)
    {
      set_timer_2(3000);
      v_sbutton_click++;
      set_timer(500);
      v_sbutton_process = STATE_CLICK;
    }
    break;
  default:
    v_sbutton_process = STATE_INIT;
    break;
  }
}

char time_out()
{
  if (v_sbutton_timeout)
  {
    v_sbutton_timeout = 0;
    return 1;
  }
  return 0;
}

char time_out_2()
{
  if (v_sbutton_timeout_2)
  {
    v_sbutton_timeout_2 = 0;
    return 1;
  }
  return 0;
}

void set_timer(int time)
{
  v_sbutton_timer = time;
  v_sbutton_timeout = 0;
}

void set_timer_2(int time)
{
  v_sbutton_timer_2 = time;
  v_sbutton_timeout_2 = 0;
}

/* End of file -------------------------------------------------------- */
