/**
 * @file       driver_button.c
 * @copyright
 * @license
 * @version
 * @date       2024-07-07
 * @author     Hung Nguyen Nhat
 *
 * @brief      This file include the following function
 *             - Initialize GPIO pin for button function
 *             - Read button status with debounce for 50ms
 *
 * @note
 * @example
 */

/* Includes ----------------------------------------------------------- */
#include "driver_button.h"

/* Private defines ---------------------------------------------------- */
#define NO_EVENT (0)      /* event ID when there is no edge on GPIO pin */
#define EDGE_EVENT (1)    /* event ID when there is an edge on GPIO pin */
#define TIMEOUT_EVENT (2) /* event ID when edge on GPIO pin is validated */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */
/**
 * @brief  This function will count the tick from Systick Timer to measure
 * the time for debouncing button
 *
 * @param[in]     v_dbutton  <struct pointer managing the button needing to be debounced>
 *
 * @attention  <API attention note>
 *
 * @return
 *  - tick - (v_dbutton->button_tick) if Systick Timer counter hasn't overflowed
 *  - tick + 1 + 0xFFFFFFFF - (v_dbutton->button_tick) if Systick Timer counter has overflowed
 */
static uint32_t driver_button_tick(driver_button_t* v_dbutton);
/* Function definitions ----------------------------------------------- */
driver_state_t driver_button_init(driver_button_t* v_dbutton)
{
  DRIVER_CHECK_NULL(v_dbutton, DRIVER_STATE_FAIL);
  uint16_t port, pin;
  GPIO_InitTypeDef GPIO_InitStruct = { 0 };
  port = (v_dbutton->button_pin.io) & 0x00F0;
  pin = (v_dbutton->button_pin.io) & 0x000F;
  switch (port)
  {
  case DRIVER_MCU_PORT_A:
  {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = (uint16_t)1 << pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    v_dbutton->button_io_preState = HAL_GPIO_ReadPin(GPIOA, (uint16_t)1 << pin);
    break;
  }
  case DRIVER_MCU_PORT_D:
  {
    __HAL_RCC_GPIOD_CLK_ENABLE();
    GPIO_InitStruct.Pin = (uint16_t)1 << pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    v_dbutton->button_io_preState = HAL_GPIO_ReadPin(GPIOD, (uint16_t)1 << pin);
    break;
  }
  }
  return DRIVER_STATE_PASS;
}

driver_button_state_t driver_button_read(driver_button_t* v_dbutton)
{
  DRIVER_CHECK_NULL(v_dbutton, DRIVER_BUTTON_STATE_NO_READ);
  uint16_t port, pin;
  GPIO_PinState state;
  static uint8_t event_flag = NO_EVENT;

  port = (v_dbutton->button_pin.io) & 0x00F0;
  pin = (v_dbutton->button_pin.io) & 0x000F;
  switch (port)
  {
  case DRIVER_MCU_PORT_A:
  {
    state = HAL_GPIO_ReadPin(GPIOA, (uint16_t)1 << pin);
    break;
  }
  case DRIVER_MCU_PORT_D:
  {
    state = HAL_GPIO_ReadPin(GPIOD, (uint16_t)1 << pin);
    break;
  }
  }

  /* Check whether an edge occur on gpio input */
  if (state != (v_dbutton->button_io_preState))
  {
    if (event_flag == NO_EVENT)
    {
      event_flag = EDGE_EVENT;
      v_dbutton->button_tick = HAL_GetTick();
    }
    else if ((driver_button_tick(v_dbutton) > 30) && (event_flag == EDGE_EVENT))
    {
      event_flag = TIMEOUT_EVENT;
    }
  }
  else if (state == (v_dbutton->button_io_preState))
  {
    event_flag = NO_EVENT;
  }

  /* This execute when the change is validated and io_preState is updated */

  if (event_flag == TIMEOUT_EVENT)
  {
    event_flag = NO_EVENT;
    (v_dbutton->button_io_preState) = state;
  }

  /* return button state base button type */
  if ((v_dbutton->button_type) == DRIVER_BUTTON_TYPE_PD)
  {
    if ((v_dbutton->button_io_preState) == GPIO_PIN_RESET)
      return DRIVER_BUTTON_STATE_NO_PUSHED;
    else
      return DRIVER_BUTTON_STATE_IS_PUSHED;
  }
  else
  {
    if ((v_dbutton->button_io_preState) == GPIO_PIN_SET)
      return DRIVER_BUTTON_STATE_NO_PUSHED;
    else
      return DRIVER_BUTTON_STATE_IS_PUSHED;
  }
}
/* Private definitions ----------------------------------------------- */
static uint32_t driver_button_tick(driver_button_t* v_dbutton)
{
  uint32_t tick;
  tick = HAL_GetTick();
  if (tick > (v_dbutton->button_tick))
  {
    return tick - (v_dbutton->button_tick);
  }
  else
    return tick + 1 + 0xFFFFFFFF - (v_dbutton->button_tick);
}
/* End of file -------------------------------------------------------- */
