/**
 * @file       sys_manager.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    
 * @version    1.0.0
 * @date       2024-08-07
 * @author     Hung Nguyen
 *             
 * @brief      <A brief description of the content of the file>
 *             
 * @note          
 * @example    
 * 
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __SYS_MANAGER_H
#define __SYS_MANAGER_H

/* Includes ----------------------------------------------------------- */
#include "fifo_buffer.h"
#include "sys_data.h"
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */

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
 void sys_manager_init(fifo_buffer_info_t **req_list, fifo_buffer_int **ev_list);

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
void sys_manager_loop(void);
#endif // __SYS_MANAGER_H

/* End of file -------------------------------------------------------- */
