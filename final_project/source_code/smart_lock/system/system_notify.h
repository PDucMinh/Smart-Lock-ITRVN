/**
 * @file       system_notify.h
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

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __SYSTEM_NOTIFY_H
#define __SYSTEM_NOTIFY_H

/* Includes ----------------------------------------------------------- */

/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief <enum descriptiton>
 */
typedef enum 
{
  UNLOCKED,
  LOCKED,
  WRONG_PASSWORD,
  CORRECT_PASSWORD
} system_notify_state_t;

typedef enum
{
  SYS_NOTI_OK,
  SYS_NOTI_ERROR
} system_notify_return_t;
/**
 * @brief <structure descriptiton>
 */


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
void system_notify_init(void);

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
system_notify_return_t system_notify_set(system_notify_state_t state); 

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

system_notify_state_t system_notify_get_state(void);

#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
