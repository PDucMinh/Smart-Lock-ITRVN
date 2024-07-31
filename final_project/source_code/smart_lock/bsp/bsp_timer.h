/**
 * @file       bsp_timer.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license
 * @version    1.0.0
 * @date       2024-07-31
 * @author     Hung Nguyen
 *
 * @brief      <A brief description of the content of the file>
 *
 * @note
 * @example
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H

/* Includes ----------------------------------------------------------- */
#include "stm32f4xx_hal.h"
#include "bsp_config.h"
#include "bsp_mcu.h"
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
bsp_state_t bsp_timer_init(bsp_mcu_t* mcu);
bsp_state_t bsp_timer_start(void);
bsp_state_t bsp_timer_register_callback(void (*callback)(void), bsp_mcu_t* mcu);
#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
