/**
 * @file       bsp_gpio.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license
 * @version    1.0.0
 * @date       2024-07-27
 * @author     Hung Nguyen
 *
 * @brief      This file export gpio init API
 *
 * @note
 * @example
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

/* Includes ----------------------------------------------------------- */
#include "stm32f4xx_hal.h"
#include "bsp_state.h"
/* Public defines ----------------------------------------------------- */
/* gpio port ID */
#define BSP_GPIO_PORT_A (0x00)
#define BSP_GPIO_PORT_B (0x01)
#define BSP_GPIO_PORT_C (0x02)
#define BSP_GPIO_PORT_D (0x03)
#define BSP_GPIO_PORT_E (0x04)
/* gpio pin ID */
#define BSP_GPIO_PIN_0 (0x00)
#define BSP_GPIO_PIN_1 (0x01)
#define BSP_GPIO_PIN_2 (0x02)
#define BSP_GPIO_PIN_3 (0x03)
#define BSP_GPIO_PIN_4 (0x04)
#define BSP_GPIO_PIN_5 (0x05)
#define BSP_GPIO_PIN_6 (0x06)
#define BSP_GPIO_PIN_7 (0x07)
#define BSP_GPIO_PIN_8 (0x08)
#define BSP_GPIO_PIN_9 (0x09)
#define BSP_GPIO_PIN_10 (0x0A)
#define BSP_GPIO_PIN_11 (0x0B)
#define BSP_GPIO_PIN_12 (0x0C)
#define BSP_GPIO_PIN_13 (0x0D)
#define BSP_GPIO_PIN_14 (0x0E)
#define BSP_GPIO_PIN_15 (0x0F)
/* gpio pin mode ID */
#define BSP_GPIO_INPUT (GPIO_MODE_INPUT)
#define BSP_GPIO_OUTPUT_PP (GPIO_MODE_OUTPUT_PP)
#define BSP_GPIO_OUTPUT_OD (GPIO_MODE_OUTPUT_OD)
#define BSP_GPIO_AF_PP (GPIO_MODE_AF_PP)
#define BSP_GPIO_AF_OD (GPIO_MODE_AF_OD)
#define BSP_GPIO_ANALOG (GPIO_MODE_ANALOG)
/* gpio pin speed ID */
#define BSP_GPIO_FREQ_VERY_HIGH (GPIO_SPEED_FREQ_VERY_HIGH)
#define BSP_GPIO_FREQ_HIGH (GPIO_SPEED_FREQ_HIGH)
#define BSP_GPIO_FREQ_MEDIUM (GPIO_SPEED_FREQ_MEDIUM)
#define BSP_GPIO_FREQ_LOW (GPIO_SPEED_FREQ_LOW)
/* gpio pin resistor type */
#define BSP_GPIO_PULLUP (GPIO_PULLUP)
#define BSP_GPIO_PULLDOWN (GPIO_PULLDOWN)
#define BSP_GPIO_NOPULL (GPIO_NOPULL)
/* gpio pin alternate function ID */
#define BSP_GPIO_AF0 (0x00)
#define BSP_GPIO_AF1 (0x01)
#define BSP_GPIO_AF2 (0x02)
#define BSP_GPIO_AF3 (0x03)
#define BSP_GPIO_AF4 (0x04)
#define BSP_GPIO_AF5 (0x05)
#define BSP_GPIO_AF6 (0x06)
#define BSP_GPIO_AF7 (0x07)
#define BSP_GPIO_AF8 (0x08)
#define BSP_GPIO_AF9 (0x09)
#define BSP_GPIO_AF10 (0x0A)
#define BSP_GPIO_AF12 (0x0C)
#define BSP_GPIO_AF15 (0x0F)

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief enum definition for gpio pin state
 */
typedef enum
{
  BSP_GPIO_SET = GPIO_PIN_SET,
  BSP_GPIO_RESET = GPIO_PIN_RESET,
  BSP_GPIO_PIN_ERROR
} bsp_gpio_pin_state_t;

/**
 * @brief struct manage gpio pin
 */
typedef struct
{
  uint16_t io;
  uint16_t af;
  uint16_t mode;
  uint16_t pull_type;
  uint16_t speed;
} bsp_gpio_pin_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  API for init gpio pin
 *
 * @param[in]     pin  struct manage gpio pin
 *
 * @attention  This API will be called one time only
 *
 * @return     none
 *
 */
bsp_state_t bsp_gpio_pin_init(bsp_gpio_pin_t *bgpio);

/**
 * @brief  API for reading status of gpio pin
 *
 * @param[in]     pin  struct manage gpio pin
 *
 * @attention  This API will be called one time only
 *
 * @return     none
 *
 */
bsp_gpio_pin_state_t bsp_gpio_pin_read(bsp_gpio_pin_t *bgpio);
#endif // __BSP_GPIO_H

/* End of file -------------------------------------------------------- */
