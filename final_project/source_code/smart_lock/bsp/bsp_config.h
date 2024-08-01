/**
 * @file       bsp_config.h
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
#ifndef __BSP_CONFIG_H
#define __BSP_CONFIG_H

/* Includes ----------------------------------------------------------- */
#include "stm32f4xx_hal.h"
#include "bsp_exti.h"
#include "bsp_gpio.h"
/* Public defines ----------------------------------------------------- */
#define BSP_CONFIG_LED_RED   TIM_CHANNEL_1
#define BSP_CONFIG_LED_GREEN TIM_CHANNEL_2
#define BSP_CONFIG_LED_BLUE  TIM_CHANNEL_3

#define BSP_CONFIG_IR_IT_LINE  BSP_EXTI_LINE_2
#define BSP_CONFIG_IR_PIN      ((BSP_GPIO_PORT_A << 4) | BSP_GPIO_PIN_2)

#define BSP_CONFIG_BUZZER_CHANNEL TIM_CHANNEL_1
/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  BSP_CONFIG_ID_LED_RGB,
  BSP_CONFIG_ID_BUZZER,
  BSP_CONFIG_ID_IR,
  BSP_CONFIG_ID_MAX
}bsp_config_id_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
