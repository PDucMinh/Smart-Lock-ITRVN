/**
 * @file       drv_ir.h
 * @copyright
 * @license
 * @version    1.0.0
 * @date       2024-07-30
 * @author     Phat Nguyen Tan
 * @author
 *
 * @brief      <This file is header file for module infrared sensor>
 *
 * @note
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __DRV_IR_H
#define __DRV_IR_H

/* Includes ----------------------------------------------------------- */
#include <stdbool.h>
#include "bsp_config.h"
#include "bsp_exti.h"
#include "bsp_gpio.h"
#include "bsp_state.h"
/* Public defines ---------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief infrared sensor state
 */
typedef enum
{
  DRV_IR_STATE_IS_OBSTACLE,
  DRV_IR_STATE_NO_OBSTACLE,
} drv_ir_state_t;

/**
 * @brief <structure descriptiton>
 */
typedef struct
{
  uint32_t debounce_tick_start;           /**< define debounce time */
  bool (*exti_event)(uint16_t exti_line); /**< function pointer to detect external event */
  bool (*gpio_state)(uint16_t pin);       /**< function pointer to detect gpio state */
} drv_ir_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  <function description>
 *
 * @param[in]     <drv_ir_t *ir>  <param_despcription>
 * @param[out]    None
 * @param[inout]  None
 *
 * @attention  <API attention note>
 *
 * @return
 * - 0: BSP_STATE_FAIL
 * - 1: BSP_STATE_PASS
 */
bsp_state_t drv_ir_init(drv_ir_t* ir);

/**
 * @brief  <this function utilized to get sensor status>
 *
 * @param[in]     None
 * @param[out]    None
 * @param[inout]  None
 * @return
 *  - 0: DRV_IR_STATE_IS_OBSTACLE
 *  - 1: DRV_IR_STATE_NO_OBSTACLE
 */
drv_ir_state_t drv_ir_state(drv_ir_t* ir);

#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
