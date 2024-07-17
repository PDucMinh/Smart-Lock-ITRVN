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
#define DRIVER_MCU_PORT_A (0x00)
#define DRIVER_MCU_PORT_B (0x01)
#define DRIVER_MCU_PORT_C (0x02)
#define DRIVER_MCU_PORT_D (0x03)
#define DRIVER_MCU_PORT_E (0x04)
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
/* gpio pin mode ID */
#define DRIVER_MCU_PIN_INPUT     (GPIO_MODE_INPUT)
#define DRIVER_MCU_PIN_OUTPUT_PP (GPIO_MODE_OUTPUT_PP)
#define DRIVER_MCU_PIN_OUTPUT_OD (GPIO_MODE_OUTPUT_OD)
#define DRIVER_MCU_PIN_AF_PP     (GPIO_MODE_AF_PP)
#define DRIVER_MCU_PIN_AF_OD     (GPIO_MODE_AF_OD)
#define DRIVER_MCU_PIN_ANALOG    (GPIO_MODE_ANALOG)
/* gpio pin speed ID */
#define DRIVER_MCU_PIN_VERY_HIGH (GPIO_SPEED_FREQ_VERY_HIGH)
#define DRIVER_MCU_PIN_HIGH      (GPIO_SPEED_FREQ_HIGH)
#define DRIVER_MCU_PIN_MEDIUM    (GPIO_SPEED_FREQ_MEDIUM)
#define DRIVER_MCU_PIN_LOW       (GPIO_SPEED_FREQ_LOW)
/* gpio pin resistor type */
#define DRIVER_MCU_PIN_PULLUP    (GPIO_PULLUP)
#define DRIVER_MCU_PIN_PULLDOWN  (GPIO_PULLDOWN)
#define DRIVER_MCU_PIN_NOPULL    (GPIO_NOPULL)
/* gpio pin alternate function ID */
#define DRIVER_MCU_PIN_AF0    (0x00)
#define DRIVER_MCU_PIN_AF1    (0x01) 
#define DRIVER_MCU_PIN_AF2    (0x02)
#define DRIVER_MCU_PIN_AF3    (0x03)
#define DRIVER_MCU_PIN_AF4    (0x04)
#define DRIVER_MCU_PIN_AF5    (0x05)
#define DRIVER_MCU_PIN_AF6    (0x06)
#define DRIVER_MCU_PIN_AF7    (0x07)
#define DRIVER_MCU_PIN_AF8    (0x08)
#define DRIVER_MCU_PIN_AF9    (0x09)
#define DRIVER_MCU_PIN_AF10   (0x0A)
#define DRIVER_MCU_PIN_AF12   (0x0C)
#define DRIVER_MCU_PIN_AF15   (0x0F)
/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief <enum descriptiton>
 */
typedef enum 
{
  DRIVER_MCU_TIM_CHANNEL_1 = 0x0000, /**< Description of PUBLIC_ENUM_1 */
  DRIVER_MCU_TIM_CHANNEL_2 = 0x0004, /**< Description of PUBLIC_ENUM_2 */
  DRIVER_MCU_TIM_CHANNEL_3 = 0x0008,
  DRIVER_MCU_TIM_CHANNEL_4 = 0x000C,
  DRIVER_MCU_TIM_NO_CHANNEL = 0x000E  /**< Description of PUBLIC_ENUM_3 */
}
driver_mcu_tim_channel_t;

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
  uint16_t io; /**< Description of member_2 */
  uint16_t af;
  uint16_t mode;
  uint16_t pull_type;
  uint16_t speed;
} driver_mcu_pin_t;
/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  <Initializing flash functionality and enabling clock source for 
 *          peripheral module>
 *
 * @param[in]     <v_dmcu>  <struct pointer manage properties of MCU>
 * @param[out]    
 * @param[inout]  
 *
 * @attention  
 *
 * @return
 *  - DRIVER_STATE_PASS: Success
 *  - DRIVER_STATE_FAIL: Error
 */
driver_state_t driver_mcu_init(driver_mcu_t* v_dmcu);
/**
 * @brief  <Initializing GPIO pin function> 
 *          
 *
 * @param[in]     <v_dmcu>  <struct pointer manage properties of MCU>
 * @param[out]    
 * @param[inout]  
 *
 * @attention  
 *
 * @return
 *  - DRIVER_STATE_PASS: Success
 *  - DRIVER_STATE_FAIL: Error
 */
driver_state_t driver_mcu_pin_init(driver_mcu_pin_t* v_dpin);

#endif // __DRIVER_MCU_H

/* End of file -------------------------------------------------------- */
