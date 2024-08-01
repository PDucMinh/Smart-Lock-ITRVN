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
/* Private variables -------------------------------------------------- */
uint8_t callback_flag = 0;
/* Private function prototypes ---------------------------------------- */
static void drv_ir_debounce_callback(void);
/* Function definitions ----------------------------------------------- */
drv_ir_status_t drv_ir_init(drv_ir_t *ir)
{
  if (ir == NULL)
  {
    return DRV_IR_STATUS_FAIL;
  }
  ir->debounce_flag = 0;
  ir->exti_event = bsp_exti_event;
  ir->gpio_state = bsp_gpio_pin_read;

  return DRV_IR_STATUS_SUCCESS;
}

drv_ir_state_t drv_ir_state(drv_ir_t *ir)
{
  if ((ir->exti_event(BSP_CONFIG_IR_IT_LINE) == 1) && (ir->debounce_flag == 0))
  {
    // Update debounce tick start
    ir->debounce_flag = 1;
    sch_add_task(drv_ir_debounce_callback, 1, 100);
  }

  // Check debounce state
  if ((ir->debounce_flag == 1) && (callback_flag == 1))
  {
    ir->debounce_flag = 0;
    callback_flag = 0;
    if (ir->gpio_state(BSP_CONFIG_IR_PIN) == 0)
    {
      return DRV_IR_STATE_IS_OBSTACLE;
    }
    else
    {
      return DRV_IR_STATE_NO_OBSTACLE;
    }
  }
  return DRV_IR_STATE_NO_OBSTACLE;
}
/* Private definitions ----------------------------------------------- */
static void drv_ir_debounce_callback(void)
{
  callback_flag = 1;
}
/* End of file -------------------------------------------------------- */
