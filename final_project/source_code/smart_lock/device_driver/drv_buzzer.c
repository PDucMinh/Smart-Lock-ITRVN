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

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static uint8_t duration_flag = 0;

/* Private function prototypes ---------------------------------------- */
void drv_buzzer_duration_callback(void);
/* Function definitions ----------------------------------------------- */
drv_buzzer_status_t drv_buzzer_init(drv_buzzer_t* buzzer)
{
  if (buzzer == NULL)
  {
    return DRV_BUZZER_STATUS_FAIL;
  }
  buzzer->pwm_start = bsp_pwm_start;
  buzzer->pwm_stop = bsp_pwm_stop;
  buzzer->pwm_set_freq = bsp_pwm_set_freq;
  buzzer->pwm_set_duty = bsp_pwm_set_duty;
  duration_flag = 0;

  return DRV_BUZZER_STATUS_SUCCESS;
}

drv_buzzer_status_t drv_buzzer_set_note(drv_buzzer_t* buzzer, uint16_t note, uint32_t duration)
{
  if (buzzer == NULL)
  {
    return DRV_BUZZER_STATUS_FAIL;
  }

  // Set cycle
  if (note == 0)
  {
    buzzer->pwm_set_duty(BSP_CONFIG_ID_BUZZER, BSP_CONFIG_BUZZER_CHANNEL, 100);
  }
  else
  {
    float cycle_in_ms = (1.0 / note) * 1000 * 100;
    buzzer->pwm_set_freq(BSP_CONFIG_ID_BUZZER, BSP_CONFIG_BUZZER_CHANNEL, (uint32_t)cycle_in_ms);
  }

  // Set timer to stop after a duration
  sch_add_task(drv_buzzer_duration_callback, duration, 0);

  return DRV_BUZZER_STATUS_SUCCESS;
}

uint8_t drv_buzzer_duration_cplt(drv_buzzer_t* buzzer)
{
  if (buzzer == NULL)
  {
    return DRV_BUZZER_STATUS_FAIL;
  }
  uint8_t ret_flag = duration_flag;

  // Stop PWM
  if (duration_flag == 1)
  {
    duration_flag = 0;
  }
  // Set duration_flag to indicate completion

  return ret_flag;
}

drv_buzzer_status_t drv_buzzer_active(drv_buzzer_t* buzzer)
{
  if (buzzer == NULL)
  {
    return DRV_BUZZER_STATUS_FAIL;
  }
  buzzer->pwm_set_duty(BSP_CONFIG_ID_BUZZER, BSP_CONFIG_BUZZER_CHANNEL, 100);
  buzzer->pwm_start(BSP_CONFIG_ID_BUZZER, BSP_CONFIG_BUZZER_CHANNEL);
}

drv_buzzer_status_t drv_buzzer_deactive(drv_buzzer_t* buzzer)
{
  if (buzzer == NULL)
  {
    return DRV_BUZZER_STATUS_FAIL;
  }
  buzzer->pwm_set_duty(BSP_CONFIG_ID_BUZZER, BSP_CONFIG_BUZZER_CHANNEL, 100);
  buzzer->pwm_stop(BSP_CONFIG_ID_BUZZER, BSP_CONFIG_BUZZER_CHANNEL);
}
/* Private definitions ----------------------------------------------- */
void drv_buzzer_duration_callback(void)
{
  duration_flag = 1;
}
/* End of file -------------------------------------------------------- */
