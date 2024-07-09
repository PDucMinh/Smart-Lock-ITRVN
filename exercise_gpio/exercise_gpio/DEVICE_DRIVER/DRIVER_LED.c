/**
 * @file       DRIVER_LED.c
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
#include "DRIVER_LED.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/**
 * @brief  Macro check whether the first parameter is equal to NULL. If it's
 * equal to NULL then return DRIVER_FAIL for second parameter, else return
 * DRIVER_PASS.
 *
 * @param[in]     A  <parameter need to be checked>
 * @param[out]    B  <parameter receive return value>
 *
 * @attention
 *
 * @return
 *  - DRIVER_PASS: first parameter is valid
 *  - DRIVER_FAIL: first parameter is invalid 
 */
#define CHECK_NULL(A, B) \
  do                     \
  {                      \
    if (!(A != NULL))    \
      B = DRIVER_FAIL;   \
  } while (0)
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
driver_state_t driver_led_init(driver_led_t *dl)
{
  driver_state_t errorCode = DRIVER_PASS;
  CHECK_NULL(dl, errorCode);
  if (errorCode == DRIVER_FAIL)
  {
    return errorCode;
  }
  uint16_t port, pin;
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  port = (dl->led_io) & 0x00F0;
  pin = (dl->led_io) & 0x000F;
  switch (port)
  {
  case DRIVER_MCU_PORT_A:
  {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = (uint16_t)1 << pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    driver_led_set(dl, DRIVER_LED_OFF);
    break;
  }
  case DRIVER_MCU_PORT_D:
  {
    __HAL_RCC_GPIOD_CLK_ENABLE();
    GPIO_InitStruct.Pin = (uint16_t)1 << pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    driver_led_set(dl, DRIVER_LED_OFF);
    break;
  }
  }
  return DRIVER_PASS;
}

driver_state_t driver_led_set(driver_led_t *dl, driver_led_set_t state)
{
  driver_state_t errorCode = DRIVER_PASS;
  CHECK_NULL(dl, errorCode);
  if (errorCode == DRIVER_FAIL)
  {
    return errorCode;
  }
  uint16_t port, pin;
  port = (dl->led_io) & 0x00F0;
  pin = (dl->led_io) & 0x000F;
  switch (port)
  {
  case DRIVER_MCU_PORT_A:
  {
    if ((dl->led_type) == DRIVER_LED_ACOMMON)
    {
      if (state == DRIVER_LED_ON)
        HAL_GPIO_WritePin(GPIOA, ((uint16_t)1 << pin), GPIO_PIN_RESET);
      else if (state == DRIVER_LED_OFF)
        HAL_GPIO_WritePin(GPIOA, ((uint16_t)1 << pin), GPIO_PIN_SET);
    }
    else if ((dl->led_type) == DRIVER_LED_KCOMMON)
    {
      if (state == DRIVER_LED_ON)
        HAL_GPIO_WritePin(GPIOA, ((uint16_t)1 << pin), GPIO_PIN_SET);
      else if (state == DRIVER_LED_OFF)
        HAL_GPIO_WritePin(GPIOA, ((uint16_t)1 << pin), GPIO_PIN_RESET);
    }
    break;
  }
  case DRIVER_MCU_PORT_D:
  {
    if ((dl->led_type) == DRIVER_LED_ACOMMON)
    {
      if (state == DRIVER_LED_ON)
        HAL_GPIO_WritePin(GPIOD, ((uint16_t)1 << pin), GPIO_PIN_RESET);
      else if (state == DRIVER_LED_OFF)
        HAL_GPIO_WritePin(GPIOD, ((uint16_t)1 << pin), GPIO_PIN_SET);
    }
    else if ((dl->led_type) == DRIVER_LED_KCOMMON)
    {
      if (state == DRIVER_LED_ON)
        HAL_GPIO_WritePin(GPIOD, ((uint16_t)1 << pin), GPIO_PIN_SET);
      else if (state == DRIVER_LED_OFF)
        HAL_GPIO_WritePin(GPIOD, ((uint16_t)1 << pin), GPIO_PIN_RESET);
    }
    break;
  }
  }
  return DRIVER_PASS;
}
/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
