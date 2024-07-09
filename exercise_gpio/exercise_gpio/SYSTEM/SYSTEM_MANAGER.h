/**
 * @file       SYSTEM_MANAGER.h
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
#include "DRIVER_BUTTON.h"
#include "DRIVER_LED.h"
#include "DRIVER_MCU.h"

/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief <State of sysytem>
 */
typedef enum
{
  SYSTEM_LED1_ON, /**< In this state, Led 1 on, Led 2 and Led 3 off */
  SYSTEM_LED2_ON, /**< In this state, Led 2 on, Led 1 and Led 3 off */
  SYSTEM_LED3_ON, /**< In this state, Led 3 on, Led 1 and Led 2 off */
  SYSTEM_HOLD,    /**< In this state, system detect hold, all led off */
  SYSTEM_IDLE     /**< State idle */
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
void system_manager_init(driver_button_t* db, driver_led_t* dl);
void system_manager_loop(driver_button_t* db, driver_led_t* dl);

#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
