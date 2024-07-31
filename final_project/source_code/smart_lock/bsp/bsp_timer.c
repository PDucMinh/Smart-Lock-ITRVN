/**
 * @file       bsp_timer.c
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

/* Includes ----------------------------------------------------------- */
#include "bsp_timer.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
void (*callback_handler)(void);
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
static void bsp_timer_it_handler(TIM_HandleTypeDef* htim);
/* Function definitions ----------------------------------------------- */
bsp_state_t bsp_timer_init(bsp_mcu_t* mcu)
{
  BSP_CHECK_NULL(mcu, BSP_STATE_FAIL);
  (mcu->htim2).PeriodElapsedCallback = bsp_timer_it_handler;
  return BSP_STATE_FAIL;
}

bsp_state_t bsp_timer_start(bsp_mcu_t* mcu)
{
  BSP_CHECK_NULL(mcu, BSP_STATE_FAIL);
  HAL_TIM_Base_Start_IT(&(mcu->htim2));
  return BSP_STATE_PASS;
}

bsp_state_t bsp_timer_register_callback(void (*callback)(void))
{
  BSP_CHECK_NULL(callback, BSP_STATE_FAIL);
  callback_handler = callback;
  return BSP_STATE_PASS;
}
/* Private definitions ----------------------------------------------- */
static void bsp_timer_it_handler(TIM_HandleTypeDef* htim)
{
  if (callback_handler != NULL)
  {
    callback_handler();
  }
}
/* End of file -------------------------------------------------------- */
