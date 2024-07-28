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

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
bsp_state_t bsp_pwm_start(TIM_HandleTypeDef *htim, uint32_t channel)
{
    if (HAL_TIM_PWM_Start(htim, channel) != HAL_OK)
    {
        return BSP_STATE_FAIL;
    }
    else 
    {
        return BSP_STATE_PASS;
    }  
}

bsp_state_t bsp_pwm_stop(TIM_HandleTypeDef *htim, uint32_t channel)
{
    if (HAL_TIM_PWM_Stop(htim, channel) != HAL_OK)
    {
        return BSP_STATE_FAIL;
    }
    else 
    {
        return BSP_STATE_PASS;
    }
}

bsp_state_t bsp_pwm_set_duty(TIM_HandleTypeDef *htim, uint32_t channel, uint32_t duty)
{
    int pulse = (((htim->Init.Period + 1) * duty) / 100) - 1;
    if (__HAL_TIM_SET_COMPARE(htim, channel, pulse) != HAL_OK)
    {
       return BSP_STATE_FAIL;
    }
    else 
    {
        return BSP_STATE_PASS;
    }
}


/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
