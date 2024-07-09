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
#define NO_EVENT (0)      /* event ID when there is no edge on GPIO pin */
#define EDGE_EVENT (1)    /* event ID when there is an edge on GPIO pin */
#define TIMEOUT_EVENT (2) /* event ID when edge on GPIO pin is validated */
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
/**
 * @brief  This function will count the tick from Systick Timer to measure
 * the time for debouncing button
 *
 * @param[in]     db  <struct pointer managing the button needing to be debounced>
 * 
 * @attention  <API attention note>
 *
 * @return
 *  - tick - (db->button_tick) if Systick Timer counter hasn't overflowed
 *  - tick + 1 + 0xFFFFFFFF - (db->button_tick) if Systick Timer counter has overflowed
 */
static uint32_t debounce_tick_cnt(driver_button_t *db);
/* Function definitions ----------------------------------------------- */
driver_state_t driver_button_init(driver_button_t *db)
{
  driver_state_t errorCode = DRIVER_PASS;
  CHECK_NULL(db, errorCode);
  if (errorCode == DRIVER_FAIL)
  {
    return errorCode;
  }
  uint16_t port, pin;
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  port = (db->button_io) & 0x00F0;
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
  GPIO_PinState state;
  static uint8_t event_flag = NO_EVENT;

  port = (db->button_io) & 0x00F0;
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
    else if ((debounce_tick_cnt(db) > 30) && (event_flag == EDGE_EVENT))
    {
      event_flag = TIMEOUT_EVENT;
    }
  }
  else if (state == (db->button_io_preState))
  {
    event_flag = NO_EVENT;
  }

  /* This execute when the change is validated and io_preState is updated */

  if (event_flag == TIMEOUT_EVENT)
  {
    event_flag = NO_EVENT;
    (db->button_io_preState) = state;
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
