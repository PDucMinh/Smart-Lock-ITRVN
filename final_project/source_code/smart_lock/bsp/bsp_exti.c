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
static void private_function(void);
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
  switch(pin)
  {
    case BSP_GPIO_PIN_0:
    HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
    break;
    case BSP_GPIO_PIN_1:
    HAL_NVIC_SetPriority(EXTI1_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);
    break;
    case BSP_GPIO_PIN_2:
    HAL_NVIC_SetPriority(EXTI3_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);
    break;
    case BSP_GPIO_PIN_3:
    HAL_NVIC_SetPriority(EXTI4_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);
    break;
    case BSP_GPIO_PIN_4:
    HAL_NVIC_SetPriority(EXTI5_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(EXTI5_IRQn);
    break;
    case BSP_GPIO_PIN_5:
    case BSP_GPIO_PIN_6:
    case BSP_GPIO_PIN_7:
    case BSP_GPIO_PIN_8:
    case BSP_GPIO_PIN_9:
    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
    break;
    case BSP_GPIO_PIN_10:
    case BSP_GPIO_PIN_11:
    case BSP_GPIO_PIN_12:
    case BSP_GPIO_PIN_13:
    case BSP_GPIO_PIN_14:
    case BSP_GPIO_PIN_15:
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
    break;
  }
  return BSP_STATE_PASS;
}
/* Private definitions ----------------------------------------------- */
static void private_function(void)
{
}
/* End of file -------------------------------------------------------- */
