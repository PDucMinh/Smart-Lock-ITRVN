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
#ifndef __DRV_MCU_H
#define __DRV_MCU_H

/* Includes ----------------------------------------------------------- */
#include "stm32f4xx_hal.h"
#include "drv.h"
/* Public defines ----------------------------------------------------- */
/* gpio port ID */
#define DRV_MCU_PORT_A (0x00)
#define DRV_MCU_PORT_B (0x01)
#define DRV_MCU_PORT_C (0x02)
#define DRV_MCU_PORT_D (0x03)
#define DRV_MCU_PORT_E (0x04)
/* gpio pin ID */
#define DRV_MCU_PIN_0 (0x00)
#define DRV_MCU_PIN_1 (0x01)
#define DRV_MCU_PIN_2 (0x02)
#define DRV_MCU_PIN_3 (0x03)
#define DRV_MCU_PIN_4 (0x04)
#define DRV_MCU_PIN_5 (0x05)
#define DRV_MCU_PIN_6 (0x06)
#define DRV_MCU_PIN_7 (0x07)
#define DRV_MCU_PIN_8 (0x08)
#define DRV_MCU_PIN_9 (0x09)
#define DRV_MCU_PIN_10 (0x0A)
#define DRV_MCU_PIN_11 (0x0B)
#define DRV_MCU_PIN_12 (0x0C)
#define DRV_MCU_PIN_13 (0x0D)
#define DRV_MCU_PIN_14 (0x0E)
#define DRV_MCU_PIN_15 (0x0F)
/* gpio pin mode ID */
#define DRV_MCU_PIN_INPUT     (GPIO_MODE_INPUT)
#define DRV_MCU_PIN_OUTPUT_PP (GPIO_MODE_OUTPUT_PP)
#define DRV_MCU_PIN_OUTPUT_OD (GPIO_MODE_OUTPUT_OD)
#define DRV_MCU_PIN_AF_PP     (GPIO_MODE_AF_PP)
#define DRV_MCU_PIN_AF_OD     (GPIO_MODE_AF_OD)
#define DRV_MCU_PIN_ANALOG    (GPIO_MODE_ANALOG)
/* gpio pin speed ID */
#define DRV_MCU_PIN_VERY_HIGH (GPIO_SPEED_FREQ_VERY_HIGH)
#define DRV_MCU_PIN_HIGH      (GPIO_SPEED_FREQ_HIGH)
#define DRV_MCU_PIN_MEDIUM    (GPIO_SPEED_FREQ_MEDIUM)
#define DRV_MCU_PIN_LOW       (GPIO_SPEED_FREQ_LOW)
/* gpio pin resistor type */
#define DRV_MCU_PIN_PULLUP    (GPIO_PULLUP)
#define DRV_MCU_PIN_PULLDOWN  (GPIO_PULLDOWN)
#define DRV_MCU_PIN_NOPULL    (GPIO_NOPULL)
/* gpio pin alternate function ID */
#define DRV_MCU_PIN_AF0    (0x00)
#define DRV_MCU_PIN_AF1    (0x01) 
#define DRV_MCU_PIN_AF2    (0x02)
#define DRV_MCU_PIN_AF3    (0x03)
#define DRV_MCU_PIN_AF4    (0x04)
#define DRV_MCU_PIN_AF5    (0x05)
#define DRV_MCU_PIN_AF6    (0x06)
#define DRV_MCU_PIN_AF7    (0x07)
#define DRV_MCU_PIN_AF8    (0x08)
#define DRV_MCU_PIN_AF9    (0x09)
#define DRV_MCU_PIN_AF10   (0x0A)
#define DRV_MCU_PIN_AF12   (0x0C)
#define DRV_MCU_PIN_AF15   (0x0F)
/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief <enum descriptiton>
 */
typedef enum 
{
  DRV_MCU_TIM_CHANNEL_1 = 0x0000, /**< Description of PUBLIC_ENUM_1 */
  DRV_MCU_TIM_CHANNEL_2 = 0x0004, /**< Description of PUBLIC_ENUM_2 */
  DRV_MCU_TIM_CHANNEL_3 = 0x0008,
  DRV_MCU_TIM_CHANNEL_4 = 0x000C,
  DRV_MCU_TIM_NO_CHANNEL = 0x000E  /**< Description of PUBLIC_ENUM_3 */
}
drv_mcu_tim_channel_t;

/**
 * @brief struct manage peripheral of MCU
 */
typedef struct
{
#ifdef HAL_TIM_MODULE_ENABLED  
  TIM_HandleTypeDef htim3; /**< Description of member_2 */
  TIM_HandleTypeDef htim4;
#endif

#ifdef HAL_UART_MODULE_ENABLED
  UART_HandleTypeDef huart6;
#endif

#ifdef HAL_I2C_MODULE_ENABLED
  I2C_HandleTypeDef hi2c1;
#endif

#ifdef HAL_DMA_MODULE_ENABLED
  DMA_HandleTypeDef hdma_usart6_rx;
  DMA_HandleTypeDef hdma_i2c1_rx;
#endif
} drv_mcu_t;
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
} drv_mcu_pin_t;
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
drv_state_t drv_mcu_init(drv_mcu_t* v_dmcu);
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
 *  - DRV_STATE_PASS: Success
 *  - DRV_STATE_FAIL: Error
 */
drv_state_t drV_mcu_pin_init(drV_mcu_pin_t* v_dpin);

#endif // __DRIVER_MCU_H

/* End of file -------------------------------------------------------- */
