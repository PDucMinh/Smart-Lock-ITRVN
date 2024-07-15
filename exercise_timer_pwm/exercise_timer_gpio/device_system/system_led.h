/**
 * @file       system_led.h
 * @copyright  
 * @license    
 * @version    
 * @date       2024-07-11
 * @author     Hung Nguyen Nhat
 * @author     <first_name_2> <last_name_2>
 *             
 * @brief      <A brief description of the content of the file>
 *             
 * @note          
 * @example    
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __SYSTEM_LED_H
#define __SYSTEM_LED_H

/* Includes ----------------------------------------------------------- */
#include "driver_led.h"
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief <event ID for system led>
 */
typedef enum 
{
  SYSTEM_LED_EVENT_ORANGE, /**< Description of PUBLIC_ENUM_1 */
  SYSTEM_LED_EVENT_VIOLET, /**< Description of PUBLIC_ENUM_2 */
  SYSTEM_LED_EVENT_YELLOW,
  SYSTEM_LED_EVENT_OFF  /**< Description of PUBLIC_ENUM_3 */
}
system_led_event_t;

/**
 * @brief <struct manage system led>
 */
typedef struct 
{
  driver_led_t ledR; /**< Description of member_1 */
  driver_led_t ledG; /**< Description of member_2 */
  driver_led_t ledB;  /**< Description of member_3 */
  uint16_t led_rgb_id[3];
}
system_led_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  <Initialize system led>
 *
 * @param[in]     <v_dmcu>  <struct pointer manage MCU's peripheral>
 * @param[in]     <v_sled>  <struct pointer manage system led>
 * @param[inout]  <none>
 *
 * @attention  <none>
 *
 * @return  
 *  - DRIVER_STATE_PASS: Success
 *  - DRIVER_STATE_FAIL: Error
 */
 driver_state_t system_led_init(system_led_t* v_sled, driver_mcu_t* v_dmcu);

/**
 * @brief  <Set led color base on event ID>
 *
 * @param[in]     <v_sled>  <struct pointer manage system led>
 * @param[in]     <v_dmcu>  <struct pointer manage MCU's peripheral>
 * @param[in]     <v_sled_event>  <system led event>
 *
 * @attention  <none>
 *
 * @return  
 *  - DRIVER_STATE_PASS: Success
 *  - DRIVER_STATE_FAIL: Error
 */
 driver_state_t system_led_set(system_led_t* v_sled, driver_mcu_t* v_dmcu, system_led_event_t v_sled_event);
#endif // __SYSTEM_LED_H

/* End of file -------------------------------------------------------- */
