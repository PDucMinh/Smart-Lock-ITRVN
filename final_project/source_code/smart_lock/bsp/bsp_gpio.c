/**
 * @file       bsp_gpio.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license
 * @version    1.0.0
 * @date       2024-07-27
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
#include "bsp_gpio.h"

/* Private defines ---------------------------------------------------- */
#define BSP_GPIO_NUM_PORT (5)
#define BSP_GPIO_NUM_PIN (16)
/* Private enumerate/structure ---------------------------------------- */
/**
 * @brief <the state of being used of MCU's pin>
 */
typedef enum
{
  BSP_GPIO_PIN_STATE_FREE,  /**< This pin is not initialized by any module */
  BSP_GPIO_PIN_STATE_USED,  /**< This pin is initialized by another module */
  BSP_GPIO_PIN_STATE_UNUSED /**< This pin is not allowed to be used        */
} bsp_gpio_pin_state_t;
/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static bsp_gpio_pin_state_t v_gpio_pin_list[BSP_GPIO_NUM_PORT][BSP_GPIO_NUM_PIN] = {
  /* MCU_PORTA */
  { BSP_GPIO_PIN_STATE_FREE,   /* PIN 0 */
    BSP_GPIO_PIN_STATE_FREE,   /* PIN 1 */
    BSP_GPIO_PIN_STATE_FREE,   /* PIN 2 */
    BSP_GPIO_PIN_STATE_FREE,   /* PIN 3 */
    BSP_GPIO_PIN_STATE_FREE,   /* PIN 4 */
    BSP_GPIO_PIN_STATE_FREE,   /* PIN 5 */
    BSP_GPIO_PIN_STATE_FREE,   /* PIN 6 */
    BSP_GPIO_PIN_STATE_FREE,   /* PIN 7 */
    BSP_GPIO_PIN_STATE_FREE,   /* PIN 8 */
    BSP_GPIO_PIN_STATE_FREE,   /* PIN 9 */
    BSP_GPIO_PIN_STATE_FREE,   /* PIN 10 */
    BSP_GPIO_PIN_STATE_UNUSED, /* PIN 11 */
    BSP_GPIO_PIN_STATE_FREE,   /* PIN 12 */
    BSP_GPIO_PIN_STATE_FREE,   /* PIN 13 */
    BSP_GPIO_PIN_STATE_FREE,   /* PIN 14 */
    BSP_GPIO_PIN_STATE_FREE }, /* PIN 15 */
  /* MCU_PORTB */
  { BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_UNUSED,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE },
  /* MCU_PORTC */
  { BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE },
  /* MCU_PORTD */
  { BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE },
  /* MCU_PORTE */
  { BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE,
    BSP_GPIO_PIN_STATE_FREE }
};
/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
void bsp_gpio_pin_init(bsp_gpio_pin_t* bgpio)
{
  uint16_t port, pin;
  port = ((bgpio->io) & 0xF0) >> 4;
  pin = (bgpio->io) & 0x0F;
  if (v_gpio_pin_list[port][pin] != BSP_GPIO_PIN_STATE_FREE)
  {
    return;
  }
  else
  {
    v_gpio_pin_list[port][pin] = BSP_GPIO_PIN_STATE_USED;
  }
  GPIO_InitTypeDef GPIO_InitStruct = { 0 };
  GPIO_InitStruct.Pin = (uint16_t)1 << pin;
  GPIO_InitStruct.Mode = bgpio->mode;
  GPIO_InitStruct.Pull = bgpio->pull_type;
  GPIO_InitStruct.Speed = bgpio->speed;
  GPIO_InitStruct.Alternate = bgpio->af;
  switch (port)
  {
  case BSP_GPIO_PORT_A:
  {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    break;
  }
  case BSP_GPIO_PORT_B:
  {
    __HAL_RCC_GPIOB_CLK_ENABLE();
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    break;
  }
  case BSP_GPIO_PORT_C:
  {
    __HAL_RCC_GPIOC_CLK_ENABLE();
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    break;
  }
  case BSP_GPIO_PORT_D:
  {
    __HAL_RCC_GPIOD_CLK_ENABLE();
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    break;
  }
  case BSP_GPIO_PORT_E:
  {
    __HAL_RCC_GPIOE_CLK_ENABLE();
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
    break;
  }
  }
}
/* Private definitions ----------------------------------------------- */
/* End of file -------------------------------------------------------- */
