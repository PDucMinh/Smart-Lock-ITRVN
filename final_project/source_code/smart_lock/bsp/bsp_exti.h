/**
 * @file       bsp_exti.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    
 * @version    1.0.0
 * @date       2024-07-30
 * @author     Hung Nguyen
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
#ifndef __BSP_EXTI_H
#define __BSP_EXTI_H

/* Includes ----------------------------------------------------------- */
#include "bsp_gpio.h"
#include "stm32f4xx_hal.h"
/* Public defines ----------------------------------------------------- */
#define BSP_EXTI_LINE_0 (0u)
#define BSP_EXTI_LINE_1 (1u)
#define BSP_EXTI_LINE_2 (2u)
#define BSP_EXTI_LINE_3 (3u)
#define BSP_EXTI_LINE_4 (4u)
#define BSP_EXTI_LINE_5_9 (5u)
#define BSP_EXTI_LINE_10_15 (6u)

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief <enum descriptiton>
 */
typedef enum 
{
  BSP_EXTI_NO_EDGE, /**< Description of PUBLIC_ENUM_1 */
  BSP_EXTI_RISING_EDGE, /**< Description of PUBLIC_ENUM_2 */
  BSP_EXTI_FALLING_EDGE,  /**< Description of PUBLIC_ENUM_3 */
  BSP_EXTI_FALLING_RISING_EDGE
}
bsp_exti_event_t;

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
 bsp_state_t bsp_exti_init(uint16_t io, bsp_exti_event_t event_type);
 uint8_t bsp_exti_event(uint16_t exti_line);

#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
