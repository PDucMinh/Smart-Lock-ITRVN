/**
 * @file       DRIVER_LED.h
 * @copyright
 * @license
 * @version
 * @date       2024-07-07
 * @author     Hung Nguyen Nhat
 * @author     <first_name_2> <last_name_2>
 *
 * @brief      <A brief description of the content of the file>
 *
 * @note
 * @example    example_file_1.c
 *             Example_1 description
 * @example    example_file_2.c
 *             Example_2 description
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __DRIVER_LED_H
#define __DRIVER_LED_H

/* Includes ----------------------------------------------------------- */
#include "DRIVER_MCU.h"
#include "DRIVER.h"
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief <enum descriptiton>
 */
typedef enum
{
  DRIVER_LED_ON,  /**< Description of PUBLIC_ENUM_1 */
  DRIVER_LED_OFF, /**< Description of PUBLIC_ENUM_2 */
} driver_led_set_t;

/**
 * @brief <enum descriptiton>
 */
typedef enum
{
  DRIVER_LED_ACOMMON, /**< Description of PUBLIC_ENUM_1 */
  DRIVER_LED_KCOMMON, /**< Description of PUBLIC_ENUM_2 */
} driver_led_type_t;

/**
 * @brief <structure descriptiton>
 */
typedef struct
{
  driver_led_type_t led_type; /**< Description of member_2 */
  uint16_t led_io;            /**< Description of member_3 */
} driver_led_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */
extern int g_var_1; /**< Description of public variable g_var_1 */
extern int g_var_2; /**< Description of public variable g_var_2 */

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
driver_state_t driver_led_init(driver_led_t* dl);
driver_state_t driver_led_set(driver_led_t* dl, driver_led_set_t state);

#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
