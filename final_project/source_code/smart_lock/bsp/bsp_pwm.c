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
#include "stm32f4xx_hal.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
enum_result_t bsp_pwm_start(TIM_HandleTypedef *htim, uint16_t channel)
{
    htim->Init.Prescaler = 0;
    htim->Init.CounterMode = TIM_COUNTERMODE_UP;
    htim->Init.Period = 9999;
    htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    
    if (HAL_TIM_PWM_Init(htim) != HAL_OK)
    {
        return FAIL;
    }

    TIM_OC_InitTypeDef sConfigOC = {0};
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    // Init duty cycle = 0
    sConfigOC.Pulse = 0; 
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    
    if (HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, channel) != HAL_OK)
    {
        return FAIL;
    }

    if (HAL_TIM_PWM_Start(htim, channel) != HAL_OK)
    {
        return FAIL;
    }

    return SUCCESS;
}

enum_result_t bsp_pwm_stop(TIM_HandleTypedef *htim, uint16_t channel)
{
    if (HAL_TIM_PWM_Stop(htim, channel) != HAL_OK)
    {
        return FAIL;
    }
    else 
    {
        return SUCCESS;
    }
}

enum_result_t bsp_pwm_set_duty(TIM_HandleTypedef *htim, uint16_t channel, uint32_t duty)
{
    TIM_OC_InitTypeDef sConfigOC = {0};

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    // set duty cycle
    sConfigOC.Pulse = (((htim->Init.Period + 1) * duty) / 100) - 1; 
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    if (HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, channel) != HAL_OK)
    {
        return FAIL;
    }

    if (HAL_TIM_PWM_Start(htim, channel) != HAL_OK)
    {
        return FAIL;
    }

    return SUCCESS;
}
/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
