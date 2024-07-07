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
  SYSTEM_BUTTON_1CLICK, /**< Description of PUBLIC_ENUM_1 */
  SYSTEM_BUTTON_2CLICK, /**< Description of PUBLIC_ENUM_2 */
  SYSTEM_BUTTON_HOLD,
  SYSTEM_BUTTON_RELEASE  /**< Description of PUBLIC_ENUM_3 */
}
system_button_state_t;

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
#define PUBLIC_MACRO(a)  do_something_with(a)

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
 system_button_state_t system_button_read(driver_button_t *db);
void system_button_loop system_button_loop(driver_button_t *db);
#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
