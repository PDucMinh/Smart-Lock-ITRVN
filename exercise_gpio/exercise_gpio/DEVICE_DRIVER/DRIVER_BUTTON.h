/**
 * @file       DRIVER_BUTTON.h
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
#ifndef __DRIVER_BUTTON_H
#define __DRIVER_BUTTON_H

/* Includes ----------------------------------------------------------- */
#include "DRIVER_MCU.h"
#include "DRIVER.h"
/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief status of button
 */
typedef enum
{
  DRIVER_BUTTON_IS_PUSHED, /**< Description of PUBLIC_ENUM_1 */
  DRIVER_BUTTON_NO_PUSHED, /**< Description of PUBLIC_ENUM_2 */
  DRIVER_BUTTON_NO_READ
} driver_button_state_t;

/**
 * @brief type of button
 */
typedef enum
{
  DRIVER_BUTTON_PULL_UP,  /**< Description of PUBLIC_ENUM_1 */
  DRIVER_BUTTON_PULL_DOWN /**< Description of PUBLIC_ENUM_2 */
} driver_button_type_t;

/**
 * @brief <structure descriptiton>
 */
typedef struct
{
  driver_button_type_t button_type; /**< Description of member_2 */
  uint16_t button_io;
  GPIO_PinState button_io_preState;
  uint32_t button_tick; /**< Description of member_3 */
} driver_button_t;

/* Public macros ------------------------------------------------------ */
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
#define PUBLIC_MACRO(a) do_something_with(a)

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
driver_state_t driver_button_init(driver_button_t* db);
driver_button_state_t driver_button_read(driver_button_t* db, driver_state_t* errorCode);

#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
