/**
 * @file       SYSTEM_BUTTON.h
 * @copyright
 * @license
 * @version
 * @date       2024-07-07
 * @author     Minh Pham Duc
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
#ifndef __SYSTEM_BUTTON_H
#define __SYSTEM_BUTTON_H

/* Includes ----------------------------------------------------------- */
#include "DRIVER_BUTTON.h"
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief <enum descriptiton>
 */
typedef enum
{
  SYSTEM_BUTTON_IDLE,
  SYSTEM_BUTTON_INIT,
  SYSTEM_BUTTON_1CLICK, /**< Description of PUBLIC_ENUM_1 */
  SYSTEM_BUTTON_2CLICK, /**< Description of PUBLIC_ENUM_2 */
  SYSTEM_BUTTON_HOLD,
  SYSTEM_BUTTON_RELEASE /**< Description of PUBLIC_ENUM_3 */
} system_button_state_t;

typedef struct
{
  system_button_state_t button_state;
  driver_button_t *button;
  driver_state_t activate;
} system_button_t;
/**
 * @brief structure manage a button
 */
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
// void system_button_init(driver_button_t* db);
void system_button_init(system_button_t *v_sbutton);
/**
 * @brief  <initialize counter before reading number of clicks>
 *
 * @param[in]     driver_button_t struct pointer manage button signal
 * @param[out]    none
 *
 * @attention  none
 *
 * @return
 *  none
 */
system_button_state_t system_button_read(system_button_t *v_sbutton);
/**
 * @brief  <read button state>
 *
 * @param[in]     driver_button_t struct pointer manage button signal
 * @param[out]    system_button_state_t  button behavior number of click or release
 *
 * @attention  none
 *
 * @return
 *  system_button_state_t: number of the button clicks
 */
void system_button_loop(system_button_t *v_sbutton);
/**
 * @brief  <button click counter run() in TIMER>
 *
 * @param[in]     driver_button_t struct pointer manage button signal
 * @param[out]    none
 *
 * @attention  none
 *
 * @return
 *  none
 */
#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
