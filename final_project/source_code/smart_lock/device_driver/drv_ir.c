/**
 * @file       drv_ir.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       2024-07-30
 * @author     Phat Nguyen Tan
 * @author
 *
 * @brief      <This file is source code file to define functions for module infrared sensor>
 *
 * @note
 */

/* Includes ----------------------------------------------------------- */
#include "drv_ir.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */
uint8_t flag = 0;
/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
drv_ir_status_t drv_ir_init(drv_ir_t* ir)
{
  if (ir == NULL)
  {
    return DRV_IR_STATUS_FAIL;
  }

  ir->debounce_tick_start = 0;
  ir->exti_event = bsp_exti_event;
  ir->gpio_state = bsp_gpio_pin_read;

  return DRV_IR_STATUS_SUCCESS;
}

drv_ir_state_t drv_ir_state(drv_ir_t* ir)
{
  if ((ir.exti_event(BSP_CONFIG_IR_LINE) == true) && (flag == 0))
  {
    // Update debounce tick start
    ir.debounce_tick_start = HAL_GetTick();
    flag = 1;
  }

  // Check debounce state
  if (flag == 1)
  {
    if ((HAL_GetTick() - ir.debounce_tick_start) >= 100)
    {
      flag = 0;
      if (ir.gpio_state(BSP_CONFIG_IR_PIN) == 0)
      {
        return DRV_IR_STATE_IS_OBSTACLE;
      }
      else
      {
        return DRV_IR_STATE_NO_OBSTACLE;
      }
    }
  }
  return DRV_IR_STATE_NO_OBSTACLE;
}
/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
