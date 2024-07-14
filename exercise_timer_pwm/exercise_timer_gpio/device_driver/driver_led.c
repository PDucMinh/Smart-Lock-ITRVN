/**
 * @file       driver_led.c
 * @copyright
 * @license
 * @version
 * @date       2024-07-08
 * @author     Hung Nguyen Nhat
 *
 * @brief      This file include the following function
 *             - Initialize GPIO pin for led function
 *             - Set led on, led off depend on the led type
 *
 * @note
 * @example
 */

/* Includes ----------------------------------------------------------- */
#include "driver_led.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
driver_state_t driver_led_init(driver_led_t *v_dled, driver_mcu_t *v_dmcu)
{
  DRIVER_CHECK_NULL(v_dled, DRIVER_STATE_FAIL);
  DRIVER_CHECK_NULL(v_dmcu, DRIVER_STATE_FAIL);
  if (driver_mcu_pin_init(&(v_dled->led_pin)) == DRIVER_STATE_FAIL)
  {
    return DRIVER_STATE_FAIL;
  }
  HAL_TIM_PWM_Start(&(v_dmcu->htim4), v_dled->led_tim_channel);
  driver_led_set(v_dmcu, v_dled, 0);
  return DRIVER_STATE_PASS;
}

driver_state_t driver_led_set(driver_mcu_t *v_dmcu, driver_led_t *v_dled, uint16_t v_dled_duty)
{
  DRIVER_CHECK_NULL(v_dled, DRIVER_STATE_FAIL);
  DRIVER_CHECK_NULL(v_dmcu, DRIVER_STATE_FAIL);
  DRIVER_CHECK_RANGE(v_dled_duty, 100, DRIVER_STATE_FAIL);
  if ((v_dled->led_type) == DRIVER_LED_TYPE_KCOMMON)
  {
    __HAL_TIM_SET_COMPARE(&(v_dmcu->htim4), v_dled->led_tim_channel, 100 * v_dled_duty);
  }
  else if ((v_dled->led_type) == DRIVER_LED_TYPE_ACOMMON)
  {
    __HAL_TIM_SET_COMPARE(&(v_dmcu->htim4), v_dled->led_tim_channel, 100 * (100 - v_dled_duty));    
  }
  else
  {
    return DRIVER_STATE_FAIL;
  }
  return DRIVER_STATE_PASS;
}
/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
