/**
 * @file       bsp_pwm.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    
 * @version    1.0.0
 * @date       2024-07-27
 * @author     Phat Nguyen
 *             
 * @brief      <A brief description of the content of the file>
 *             
 * @note          
 * @example    
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_pwm.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
bsp_state_t bsp_pwm_init(bsp_mcu_t* mcu)
{
  BSP_CHECK_NULL(mcu, BSP_STATE_FAIL);
  htim3 = mcu->htim3;
  htim4 = mcu->htim4;
  return BSP_STATE_PASS;
}

bsp_state_t bsp_pwm_start(bsp_config_id_t id, uint32_t channel)
{
  if (id == BSP_CONFIG_ID_LED_RGB)
  {
    if (HAL_TIM_PWM_Start(&htim3, channel) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }
    else
    {
      return BSP_STATE_PASS;
    }
  }
  else if (id == BSP_CONFIG_ID_BUZZER)
  {
    if (HAL_TIM_PWM_Start(&htim4, channel) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }
    else
    {
      return BSP_STATE_PASS;
    }
  }
}

bsp_state_t bsp_pwm_stop(bsp_config_id_t id, uint32_t channel)
{
  if (id == BSP_CONFIG_ID_LED_RGB)
  {
    if (HAL_TIM_PWM_Stop(&htim3, channel) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }
    else
    {
      return BSP_STATE_PASS;
    }
  }
  else if (id == BSP_CONFIG_ID_BUZZER)
  {
    if (HAL_TIM_PWM_Stop(&htim4, channel) != HAL_OK)
    {
      return BSP_STATE_FAIL;
    }
    else
    {
      return BSP_STATE_PASS;
    }
  }
}

bsp_state_t bsp_pwm_set_duty(bsp_config_id_t id, uint32_t channel, uint32_t duty)
{
  BSP_CHECK_RANGE(id, BSP_CONFIG_ID_MAX, BSP_STATE_FAIL);
  BSP_CHECK_RANGE(duty, 100, BSP_STATE_FAIL);
  int pulse;
  if (id == BSP_CONFIG_ID_LED_RGB)
  {
	  pulse = (((htim3.Init.Period + 1) * duty) / 100) - 1;
	  __HAL_TIM_SET_COMPARE(&htim3, channel, pulse);
  }
  return BSP_STATE_PASS;
}


/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
