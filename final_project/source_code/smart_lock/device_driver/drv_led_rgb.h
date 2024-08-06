/**
 * @file       drv_led_rgb.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    
 * @version    1.0.0
 * @date       2024-07-27
 * @author     Minh Pham
 *             
 * @brief      <A brief description of the content of the file>
 *             
 * @note          
 * @example    
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __DRV_LED_RGB_H
#define __DRV_LED_RGB_H

/* Includes ----------------------------------------------------------- */
#include "bsp_pwm.h"
#include "bsp_mcu.h"
#include "bsp_config.h"

/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief function status after execution
 */
typedef enum 
{
  DRV_LED_RGB_SUCCESS,
  DRV_LED_RGB_ERROR
} drv_led_rgb_status_t;

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief RGB support color
 */
typedef enum 
{
  DRV_LED_RGB_OFF,
  DRV_LED_RGB_RED,
  DRV_LED_RGB_GREEN,
  DRV_LED_RGB_BLUE,
  DRV_LED_RGB_ORANGE,
  DRV_LED_RGB_PURPLE
} drv_led_rgb_color_t;

/**
 * @brief <structure descriptiton>
 */
typedef struct 
{
  bsp_state_t (*pwm_set) (bsp_config_id_t id, uint16_t channel, uint16_t duty);
  bsp_state_t (*pwm_start) (bsp_config_id_t id, uint16_t channel); 
} drv_led_rgb_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  initial prototype 
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
drv_led_rgb_status_t drv_led_rgb_init(drv_led_rgb_t* led);

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  set state for rgb led 
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
drv_led_rgb_status_t drv_led_rgb_set(drv_led_rgb_t* led,drv_led_rgb_color_t color);

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  check rgb led state
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
drv_led_rgb_color_t drv_led_rgb_state(void);

#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
