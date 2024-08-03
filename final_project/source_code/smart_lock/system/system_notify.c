/**
 * @file       system_notify.c
 * @copyright  Copyright (C). All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    major.minor.patch
 * @date       yyyy-mm-dd
 * @author     Minh Pham Duc
 *
 * @brief      <A brief description of the content of the file>
 *
 * @note
 */

/* Includes ----------------------------------------------------------- */
#include "system_notify.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static system_notify_state_t system_notify_state;

/* Private function prototypes ---------------------------------------- */
/**
 * @brief  <function description>
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
static void private_function(void);
/* Function definitions ----------------------------------------------- */
void system_notify_init(void)
{
}

system_notify_return_t system_notify_set(system_notify_state_t state)
{
  switch (state)
  {
  case NO_NOTIFY:
    /* code */
    break;
  case UNLOCKED:
    /* code */
    break;
  case DOUBLE_LOCKED:
    /* code */
    break;
  case WRONG_PASSWORD:
    /* code */
    break;
  case CORRECT_PASSWORD:
    /* code */
    break;
  case NEED_LOCK:
    /* code */
    break;
  default:
    state = NO_NOTIFY;
    break;
  }
}

system_notify_state_t system_notify_get_state(void)
{
}
/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
