/**
 * @file       sys_lockstate.h
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

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __SYS_LOCKSTATE_H
#define __SYS_LOCKSTATE_H

/* Includes ----------------------------------------------------------- */
#include "drv_led_rgb.h"
/* #include "drv_buzzer.h" */
/* #include "drv_ir.h" */
/* #include "bsp_gpio.h" */
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
 void sys_lockstate_init(void);
 void sys_lockstate_loop(void);

#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
