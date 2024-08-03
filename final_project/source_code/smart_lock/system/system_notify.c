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
#define __EXTERNAL_MODULE_ENABLE
/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static system_notify_state_t system_notify_state;

#ifdef __EXTERNAL_MODULE_ENABLE
bsp_gpio_pin_t bbuzzer_pin;
drv_buzzer_t dbuzzer;
melody_t sound;
// bsp_mcu_init_t bstmf411_init;
#else
drv_buzzer_t dbuzzer;
melody_t sound;
#endif

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
#ifdef __EXTERNAL_MODULE_ENABLE
void system_notify_init(void)
{
  bbuzzer_pin.io = (BSP_GPIO_PORT_D << 4) | BSP_GPIO_PIN_12;
  bbuzzer_pin.mode = BSP_GPIO_AF_PP;
  bbuzzer_pin.af = BSP_GPIO_AF2;
  bbuzzer_pin.pull_type = BSP_GPIO_NOPULL;
  bbuzzer_pin.speed = BSP_GPIO_FREQ_LOW;
  bsp_gpio_pin_init(&bbuzzer_pin);
  drv_buzzer_init(&dbuzzer);
  drv_buzzer_active(&dbuzzer);
}
#else
void system_notify_init(void)
{
}
#endif

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
