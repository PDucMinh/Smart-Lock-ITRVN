/**
 * @file       system_manager.h
 * @copyright
 * @license
 * @version    1.0
 * @date       2024-07-07
 * @author     Phat Nguyen Tan
 * @author
 *
 * @brief      <This header file contain name of function for system layer>
 *
 * @note
 * @example
 *
 * @example
 *
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __SYSTEM_MANAGER_H
#define __SYSTEM_MANAGER_H

/* Includes ----------------------------------------------------------- */
#include "system_button.h"
#include "system_led.h"

/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief <State of sysytem>
 */
typedef enum
{
  SYSTEM_STATE_LED1, /**< In this state, Led 1 on, Led 2 and Led 3 off */
  SYSTEM_STATE_LED2, /**< In this state, Led 2 on, Led 1 and Led 3 off */
  SYSTEM_STATE_LED3, /**< In this state, Led 3 on, Led 1 and Led 2 off */
  SYSTEM_STATE_HOLD,    /**< In this state, system detect hold, all led off */
  SYSTEM_STATE_IDLE     /**< State idle */
} system_state_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
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
void system_manager_init(system_button_t* v_sbutton, system_led_t* v_sled, driver_mcu_t* v_dmcu);
void system_manager_loop(system_button_t* v_sbutton, system_led_t* v_sled, driver_mcu_t* v_dmcu);

#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
