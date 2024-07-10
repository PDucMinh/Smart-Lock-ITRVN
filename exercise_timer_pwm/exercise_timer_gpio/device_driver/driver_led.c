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
driver_state_t driver_led_init(driver_led_t* dled, driver_mcu_t* dmcu)
{
  DRIVER_CHECK_NULL(dled, DRIVER_STATE_FAIL);
  uint16_t port, pin;
  GPIO_InitTypeDef GPIO_InitStruct = { 0 };
  port = ((dled->led_io).dmcu_io) & 0x00F0;
  pin = ((dled->led_io).dmcu_io) & 0x000F;
  switch (port)
  {
  case DRIVER_MCU_PORT_A:
  {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = (uint16_t)1 << pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    driver_led_set(dmcu, dled, DRIVER_LED_STATE_OFF);
    break;
  }
  case DRIVER_MCU_PORT_D:
  {
    __HAL_RCC_GPIOD_CLK_ENABLE();
    GPIO_InitStruct.Pin = (uint16_t)1 << pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    HAL_TIM_PWM_Start(&(dmcu->htim4),dled->led_io.dmcu_af);
    driver_led_set(dmcu, dled, DRIVER_LED_STATE_OFF);
    break;
  }
  }
  return DRIVER_STATE_PASS;
}

driver_state_t driver_led_set(driver_mcu_t* dmcu, driver_led_t* dled, driver_led_state_t dled_state)
{
  DRIVER_CHECK_NULL(dled, DRIVER_STATE_FAIL);
  uint16_t port, pin;
  port = ((dled->led_io).dmcu_io) & 0x00F0;
  pin = ((dled->led_io).dmcu_io) & 0x000F;
  switch (port)
  {
  case DRIVER_MCU_PORT_A:
  {
    if ((dled->led_type) == DRIVER_LED_TYPE_ACOMMON)
    {
      if (dled_state == DRIVER_LED_STATE_ON)
        HAL_GPIO_WritePin(GPIOA, ((uint16_t)1 << pin), GPIO_PIN_RESET);
      else if (dled_state == DRIVER_LED_STATE_OFF)
        HAL_GPIO_WritePin(GPIOA, ((uint16_t)1 << pin), GPIO_PIN_SET);
    }
    else if ((dled->led_type) == DRIVER_LED_TYPE_KCOMMON)
    {
      if (dled_state == DRIVER_LED_STATE_ON)
        HAL_GPIO_WritePin(GPIOA, ((uint16_t)1 << pin), GPIO_PIN_SET);
      else if (dled_state == DRIVER_LED_STATE_OFF)
        HAL_GPIO_WritePin(GPIOA, ((uint16_t)1 << pin), GPIO_PIN_RESET);
    }
    break;
  }
  case DRIVER_MCU_PORT_D:
  {
    if ((dled->led_type) == DRIVER_LED_TYPE_ACOMMON)
    {
      if (dled_state == DRIVER_LED_STATE_ON)
        __HAL_TIM_SET_COMPARE(&(dmcu->htim4), dled->led_io.dmcu_af, 0);

      else if (dled_state == DRIVER_LED_STATE_OFF)
        __HAL_TIM_SET_COMPARE(&(dmcu->htim4), dled->led_io.dmcu_af, 9999);
    }
    else if ((dled->led_type) == DRIVER_LED_TYPE_KCOMMON)
    {
      if (dled_state == DRIVER_LED_STATE_ON)
        __HAL_TIM_SET_COMPARE(&(dmcu->htim4), dled->led_io.dmcu_af, 9999);
      else if (dled_state == DRIVER_LED_STATE_OFF)
        __HAL_TIM_SET_COMPARE(&(dmcu->htim4), dled->led_io.dmcu_af, 0);
    }
    if (dled_state == DRIVER_LED_STATE_BLINK)
    {
      __HAL_TIM_SET_COMPARE(&(dmcu->htim4), dled->led_io.dmcu_af, 4999);
    }
    break;
  }
  }
  return DRIVER_STATE_PASS;
}
/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
