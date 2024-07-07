/**
 * @file       <file_name>.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    major.minor.patch
 * @date       yyyy-mm-dd
 * @author     <first_name_1> <last_name_1>
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
#ifndef __SYSTEM_MANAGER_H
#define __SYSTEM_MANAGER_H

/* Includes ----------------------------------------------------------- */
/* Public defines ----------------------------------------------------- */
#define PUBLIC_DEFINE_1  (0) /*!< Description of PUBLIC_DEFINE_1 */
#define PUBLIC_DEFINE_2  (0) /*!< Description of PUBLIC_DEFINE_2 */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief <enum descriptiton>
 */
typedef enum 
{
  SYSTEM_LED1_ON, /**< Description of PUBLIC_ENUM_1 */
  SYSTEM_LED2_ON, /**< Description of PUBLIC_ENUM_2 */
  SYSTEM_LED3_ON,
  SYSTEM_OFF,  /**< Description of PUBLIC_ENUM_3 */
}
system_state_t;

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
 void system_manager_init(void);
 void system_manager_loop(void);

#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
