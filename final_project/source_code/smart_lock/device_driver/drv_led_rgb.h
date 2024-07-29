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
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief function status after execution
 */
typedef enum 
{
  DRV_LED_SUCCESS,
  DRV_LED_ERROR
} drv_led_rgb_status_t;

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief RGB support color
 */
typedef enum 
{
  LED_RGB_OFF,
  LED_RGB_RED,
  LED_RGB_GREEN,
  LED_RGB_BLUE,
  LED_RGB_ORANGE,
  LED_RGB_PURPLE
} drv_led_rgb_state_t;

/**
 * @brief <structure descriptiton>
 */


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
drv_led_rgb_status_t drv_led_rgb_init();

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
drv_led_rgb_status_t drv_led_rgb_set(drv_led_rgb_state_t color);

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
drv_led_rgb_state_t drv_led_rgb_state(void);

#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
