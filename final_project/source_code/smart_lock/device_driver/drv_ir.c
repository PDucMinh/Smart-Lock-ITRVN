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
drv_ir_t ir_sensor;
uint8_t flag = 0; 
/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
bsp_state_t drv_ir_init(drv_ir_t *ir)
{
  if (ir == NULL) 
  {
    return BSP_STATE_FAIL;
  }
    
  ir->debounce_tick_start = 0;
  ir->exti_event = a;        /////////////////// thay ten ham
  ir->gpio_state = b;        /////////////////// thay ten ham

  return BSP_STATE_PASS;
}

drv_ir_state_t drv_ir_state(void)
{
  if ((ir_sensor.exti_event(GPIO_EXTI2) == true) && (flag == 0))
  {
    // Update debounce tick start 
    ir_sensor.debounce_tick_start = HAL_GetTick();
    flag = 1;
  }
  
  // Check debounce state
  if ((HAL_GetTick() - ir_sensor.debounce_tick_start) >= 100)
  {
    flag = 0;
    if (ir_sensor.gpio_state(GPIO_PIN_2) == 0)
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

/* End of file -------------------------------------------------------- */
