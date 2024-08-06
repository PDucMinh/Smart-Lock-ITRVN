/**
 * @file       bsp_exti.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license
 * @version    1.0.0
 * @date       2024-07-30
 * @author     Hung Nguyen
 *
 * @brief      <A brief description of the content of the file>
 *
 * @note
 * @example    example_file_1.c
 *             Example_1 description
 * @example    example_file_2.c
 *             Example_2 description
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_exti.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
struct
{
  uint8_t exti0_detector; /**< Description of PUBLIC_ENUM_1 */
  uint8_t exti1_detector; /**< Description of PUBLIC_ENUM_2 */
  uint8_t exti2_detector; /**< Description of PUBLIC_ENUM_3 */
  uint8_t exti3_detector;
  uint8_t exti4_detector;
  uint8_t exti5_9_detector;
  uint8_t exti10_15_detector;
} bsp_exti_detector;
/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
bsp_state_t bsp_exti_init(uint16_t io, bsp_exti_event_t event_type)
{
  uint16_t pin;
  bsp_gpio_pin_t bgpio_init;
  bgpio_init.io = io;
  if (event_type == BSP_EXTI_FALLING_EDGE)
  {
    bgpio_init.mode = BSP_GPIO_IT_FALLING;
  }
  else if (event_type == BSP_EXTI_RISING_EDGE)
  {
    bgpio_init.mode = BSP_GPIO_IT_RISING;
  }
  else if (event_type == BSP_EXTI_FALLING_RISING_EDGE)
  {
    bgpio_init.mode = BSP_GPIO_IT_RISING_FALLING;
  }
  else
  {
    return BSP_STATE_FAIL;
  }
  bgpio_init.pull_type = BSP_GPIO_NOPULL;
  if (bsp_gpio_pin_init(&bgpio_init) == BSP_STATE_FAIL)
  {
    return BSP_STATE_FAIL;
  }
  pin = io & 0x0F;
  switch (pin)
  {
  case BSP_GPIO_PIN_0:
    HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
    break;
  case BSP_GPIO_PIN_1:
    HAL_NVIC_SetPriority(EXTI1_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);
    break;
  case BSP_GPIO_PIN_2:
    HAL_NVIC_SetPriority(EXTI2_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);
    break;
  case BSP_GPIO_PIN_3:
    HAL_NVIC_SetPriority(EXTI3_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);
    break;
  case BSP_GPIO_PIN_4:
    HAL_NVIC_SetPriority(EXTI4_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);
    break;
  case BSP_GPIO_PIN_5:
  case BSP_GPIO_PIN_6:
  case BSP_GPIO_PIN_7:
  case BSP_GPIO_PIN_8:
  case BSP_GPIO_PIN_9:
    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
    break;
  case BSP_GPIO_PIN_10:
  case BSP_GPIO_PIN_11:
  case BSP_GPIO_PIN_12:
  case BSP_GPIO_PIN_13:
  case BSP_GPIO_PIN_14:
  case BSP_GPIO_PIN_15:
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
    break;
  }
  return BSP_STATE_PASS;
}

uint8_t bsp_exti_event(uint16_t exti_line)
{
  uint8_t event_ret = 0;
  switch (exti_line)
  {
    case BSP_EXTI_LINE_0:
    event_ret = bsp_exti_detector.exti0_detector;
    bsp_exti_detector.exti0_detector = 0;
    break;
    case BSP_EXTI_LINE_1:
    event_ret = bsp_exti_detector.exti1_detector;
    bsp_exti_detector.exti1_detector = 0;
    break;
    case BSP_EXTI_LINE_2:
    event_ret = bsp_exti_detector.exti2_detector;
    bsp_exti_detector.exti2_detector = 0;
    break;
    case BSP_EXTI_LINE_3:
    event_ret = bsp_exti_detector.exti3_detector;
    bsp_exti_detector.exti3_detector = 0;
    break;
    case BSP_EXTI_LINE_4:
    event_ret = bsp_exti_detector.exti4_detector;
    bsp_exti_detector.exti4_detector = 0;
    break;
    case BSP_EXTI_LINE_5_9:
    event_ret = bsp_exti_detector.exti5_9_detector;
    bsp_exti_detector.exti5_9_detector = 0;
    break;
    case BSP_EXTI_LINE_10_15:
    event_ret = bsp_exti_detector.exti10_15_detector;
    bsp_exti_detector.exti10_15_detector = 0;
    break;
  }
  return event_ret;
}
/* Private definitions ----------------------------------------------- */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  uint16_t pin_pos = BSP_GPIO_PIN_0;
  if (GPIO_Pin != (uint16_t)1)
  {
    while (GPIO_Pin != (uint16_t)1)
    {
      GPIO_Pin = GPIO_Pin >> 1;
    	pin_pos++;
    }
  }
  switch (pin_pos)
  {
  case BSP_GPIO_PIN_0:
    bsp_exti_detector.exti0_detector = 1;
    break;
  case BSP_GPIO_PIN_1:
    bsp_exti_detector.exti1_detector = 1;
    break;
  case BSP_GPIO_PIN_2:
    bsp_exti_detector.exti2_detector = 1;
    break;
  case BSP_GPIO_PIN_3:
    bsp_exti_detector.exti3_detector = 1;
    break;
  case BSP_GPIO_PIN_4:
    bsp_exti_detector.exti4_detector = 1;
    break;
  case BSP_GPIO_PIN_5:
  case BSP_GPIO_PIN_6:
  case BSP_GPIO_PIN_7:
  case BSP_GPIO_PIN_8:
  case BSP_GPIO_PIN_9:
    bsp_exti_detector.exti5_9_detector = 1;
    break;
  case BSP_GPIO_PIN_10:
  case BSP_GPIO_PIN_11:
  case BSP_GPIO_PIN_12:
  case BSP_GPIO_PIN_13:
  case BSP_GPIO_PIN_14:
  case BSP_GPIO_PIN_15:
    bsp_exti_detector.exti10_15_detector = 1;
    break;
  }
}
/* End of file -------------------------------------------------------- */
