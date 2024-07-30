/**
 * @file       sys_lockstate.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    
 * @version    1.0.0
 * @date       2024-07-27
 * @author     Hung Nguyen
 *             
 * @brief      <A brief description of the content of the file>
 *             
 * @note          
 * @example    
 */

/* Includes ----------------------------------------------------------- */
#include "sys_lock.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */
/**
 * @brief <enum descriptiton>
 */
typedef enum 
{
  SYS_LOCK_STATE_INIT, /**< Description of PRIVATE_ENUM_1 */
  SYS_LOCK_STATE_DOOR_OPEN, /**< Description of PRIVATE_ENUM_2 */
  SYS_LOCK_STATE_DOOR_ALARM,
  SYS_LOCK_STATE_DOOR_UNLOCKED,
  SYS_LOCK_STATE_DOOR_LOCKED,
  SYS_LOCK_STATE_DOOR_DOUBLE_LOCKED,
}
sys_lock_state_t;

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

static sys_lock_state_t slock_state;
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
void sys_lock_init(void)
{

}

void sys_lock_loop(void)
{
  switch (slock_state)
  {
    case SYS_LOCK_STATE_INIT:
    break;
    case SYS_LOCK_STATE_DOOR_OPEN:
    break;
    case SYS_LOCK_STATE_DOOR_UNLOCKED:
    break;
    case SYS_LOCK_STATE_DOOR_LOCKED:
    break;
    case SYS_LOCK_STATE_DOOR_DOUBLE_LOCKED:
    break;
    case SYS_LOCK_STATE_DOOR_ALARM:
    break;
  }
}
/* Private definitions ----------------------------------------------- */
static void private_function(void)
{
}
/* End of file -------------------------------------------------------- */
