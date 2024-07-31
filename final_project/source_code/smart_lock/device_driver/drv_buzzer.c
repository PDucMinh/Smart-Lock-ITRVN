/**
 * @file       drv_buzzer.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date       2024-07-31
 * @author     Phat Nguyen Tan
 * @author
 *
 * @brief      <This file is source code file to define functions for module buzzer>
 *
 * @note
 */

/* Includes ----------------------------------------------------------- */
#include "drv_buzzer.h"

/* Private defines ---------------------------------------------------- */
#define BUZZER_CHANNEL      TIM_CHANNEL_1
#define DELAY_BEFORE_START  1
/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static uint8_t duration_flag = 0;

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
drv_buzzer_status_t drv_buzzer_init(drv_buzzer_t *buzzer)
{
    if (buzzer == NULL)
    {
        return DRV_BUZZER_STATUS_FAIL;
    }
    
    buzzer->pwm_stop = bsp_pwm_start(BSP_CONFIG_ID_BUZZER, BUZZER_CHANNEL); 
    buzzer->pwm_set_feq = bbbbbb(BSP_CONFIG_ID_BUZZER, BUZZER_CHANNEL, 0); 
    buzzer->timer_set = aaaaa((void *)drv_buzzer_duration_cplt, DELAY_BEFORE_START, 0);
    duration_flag = 0;

    return DRV_BUZZER_STATUS_SUCCESS;
}

drv_buzzer_status_t drv_buzzer_set_note(drv_buzzer_t *buzzer, uint32_t note, uint32_t duration)
{
    if (buzzer == NULL) 
    {
        return DRV_BUZZER_STATUS_FAIL;
    }

    // Reset duration_flag before set note
    duration_flag = 0;

    // Set cycle
    int cycle_in_ms = (1 / note) * 1000;
    buzzer->pwm_set_freq(BSP_CONFIG_ID_BUZZER, BUZZER_CHANNEL, cycle_in_ms);

    // Start PWM
    buzzer->pwm_start(BSP_CONFIG_ID_BUZZER, BUZZER_CHANNEL);

    // Set timer to stop after a duration
    buzzer->timer_set((void *)drv_buzzer_duration_cplt, DELAY_BEFORE_START, duration);


    return DRV_BUZZER_STATUS_SUCCESS;
}

uint8_t drv_buzzer_duration_cplt(drv_buzzer_t *buzzer) 
{
    if (buzzer == NULL) 
    {
        return DRV_BUZZER_STATUS_FAIL; 
    }

    // Stop PWM
    result = buzzer->pwm_stop(BSP_CONFIG_ID_BUZZER, BUZZER_CHANNEL);

    // Set duration_flag to indicate completion
    duration_flag = 1;

    return DRV_BUZZER_STATUS_SUCCESS; 
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */