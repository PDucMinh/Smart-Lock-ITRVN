/**
 * @file       driver_mcu.h
 * @copyright
 * @license
 * @version
 * @date       2024-07-07
 * @author     Hung Nguyen Nhat
 *
 * @brief      <A brief description of the content of the file>
 *
 * @note
 * @example
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __DRIVER_MCU_H
#define __DRIVER_MCU_H

/* Includes ----------------------------------------------------------- */
#include "stm32f4xx_hal.h"
#include "driver.h"
/* Public defines ----------------------------------------------------- */
/* gpio port ID */
#define DRIVER_MCU_PORT_A (0x10)
#define DRIVER_MCU_PORT_B (0x20)
#define DRIVER_MCU_PORT_C (0x30)
#define DRIVER_MCU_PORT_D (0x40)
/* gpio pin ID */
#define DRIVER_MCU_PIN_0 (0x00)
#define DRIVER_MCU_PIN_1 (0x01)
#define DRIVER_MCU_PIN_2 (0x02)
#define DRIVER_MCU_PIN_3 (0x03)
#define DRIVER_MCU_PIN_4 (0x04)
#define DRIVER_MCU_PIN_5 (0x05)
#define DRIVER_MCU_PIN_6 (0x06)
#define DRIVER_MCU_PIN_7 (0x07)
#define DRIVER_MCU_PIN_8 (0x08)
#define DRIVER_MCU_PIN_9 (0x09)
#define DRIVER_MCU_PIN_10 (0x0A)
#define DRIVER_MCU_PIN_11 (0x0B)
#define DRIVER_MCU_PIN_12 (0x0C)
#define DRIVER_MCU_PIN_13 (0x0D)
#define DRIVER_MCU_PIN_14 (0x0E)
#define DRIVER_MCU_PIN_15 (0x0F)
/* pwm channel ID */
#define DRIVER_MCU_PWM_1 (0x0000)
#define DRIVER_MCU_PWM_2 (0x0004)
#define DRIVER_MCU_PWM_3 (0x0008)
#define DRIVER_MCU_PWM_4 (0x000C)
/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief struct manage peripheral of MCU
 */
typedef struct
{
  TIM_HandleTypeDef htim3; /**< Description of member_2 */
  TIM_HandleTypeDef htim4;
} driver_mcu_t;
/**
 * @brief struct manage gpio pin
 */
typedef struct
{
  uint16_t dmcu_io; /**< Description of member_2 */
  uint16_t dmcu_af;
} driver_mcu_pin_t;
/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
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
driver_state_t driver_mcu_init(driver_mcu_t *dmcu);

#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
