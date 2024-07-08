/**
 * @file       DRIVER_BUTTON.c
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
#include "DRIVER_BUTTON.h"

/* Private defines ---------------------------------------------------- */
#define NO_EVENT (0)
#define EDGE_EVENT (1)
#define TIMEOUT_EVENT (2)
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/**
 * @brief  <macro description>
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
#define CHECK_NULL(A, B) \
  do                     \
  {                      \
    if (!(A != NULL))    \
      B = DRIVER_FAIL;   \
  } while (0)
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */

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
static uint32_t debounce_tick_cnt(driver_button_t *db);
/* Function definitions ----------------------------------------------- */
driver_state_t driver_button_init(driver_button_t *db)
{
  driver_state_t errorCode;
  CHECK_NULL(db, errorCode);
  if (errorCode == DRIVER_FAIL)
  {
    return errorCode;
  }
  uint16_t port, pin;
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  port = ((db->button_io) & 0x00F0) >> 4;
  pin = (db->button_io) & 0x000F;
  switch (port)
  {
  case DRIVER_MCU_PORT_A:
  {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = (uint16_t)1 << pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    db->button_io_preState = HAL_GPIO_ReadPin(GPIOA, (uint16_t)1 << pin);
    break;
  }
  case DRIVER_MCU_PORT_D:
  {
    __HAL_RCC_GPIOD_CLK_ENABLE();
    GPIO_InitStruct.Pin = (uint16_t)1 << pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    db->button_io_preState = HAL_GPIO_ReadPin(GPIOD, (uint16_t)1 << pin);
    break;
  }
  }
  return DRIVER_PASS;
}

driver_button_state_t driver_button_read(driver_button_t *db, driver_state_t *errorCode)
{
  CHECK_NULL(db, *errorCode);
  if (*errorCode == DRIVER_FAIL)
  {
    return DRIVER_BUTTON_NO_READ;
  }

  uint16_t port, pin;
  static uint8_t event_flag = NO_EVENT;
  GPIO_PinState state;
  port = ((db->button_io) & 0x00F0) >> 4;
  pin = (db->button_io) & 0x000F;
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
  if (state != (db->button_io_preState))
  {
    if (event_flag == NO_EVENT)
    {
      event_flag = EDGE_EVENT;
      db->button_tick = HAL_GetTick();
    }
    else if (debounce_tick_cnt(db) <= 30)
    {
      event_flag = NO_EVENT;
    }
  }
  else if ((debounce_tick_cnt(db) > 30) && (event_flag == EDGE_EVENT))
  {
    event_flag = TIMEOUT_EVENT;
  }

  /* This execute when the change is validated and io_preState is updated */

  if (event_flag == TIMEOUT_EVENT)
  {
    event_flag = NO_EVENT;
    db->button_io_preState = state;
  }

  /* return button state base button type */
  if ((db->button_type) == DRIVER_BUTTON_PULL_DOWN)
  {
    if ((db->button_io_preState) == GPIO_PIN_RESET)
      return DRIVER_BUTTON_NO_PUSHED;
    else
      return DRIVER_BUTTON_IS_PUSHED;
  }
  else
  {
    if ((db->button_io_preState) == GPIO_PIN_SET)
      return DRIVER_BUTTON_NO_PUSHED;
    else
      return DRIVER_BUTTON_IS_PUSHED;
  }
}
/* Private definitions ----------------------------------------------- */
static uint32_t debounce_tick_cnt(driver_button_t *db)
{
  uint32_t tick;
  tick = HAL_GetTick();
  if (tick > (db->button_tick))
  {
    return tick - (db->button_tick);
  }
  else
    return tick + 1 + 0xFFFFFFFF - (db->button_tick);
}
/* End of file -------------------------------------------------------- */
