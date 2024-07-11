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
#define PUBLIC_DEFINE_1  (0) /*!< Description of PUBLIC_DEFINE_1 */
#define PUBLIC_DEFINE_2  (0) /*!< Description of PUBLIC_DEFINE_2 */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief <event ID for system led>
 */
typedef enum 
{
  SYSTEM_LED_EVENT_LED1, /**< Description of PUBLIC_ENUM_1 */
  SYSTEM_LED_EVENT_LED2, /**< Description of PUBLIC_ENUM_2 */
  SYSTEM_LED_EVENT_LED3,
  SYSTEM_LED_EVENT_OFF  /**< Description of PUBLIC_ENUM_3 */
}
system_led_event_t;

/**
 * @brief <struct manage system led>
 */
typedef struct 
{
  driver_led_t led1; /**< Description of member_1 */
  driver_led_t led2; /**< Description of member_2 */
  driver_led_t led3;  /**< Description of member_3 */
}
system_led_t;

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
 driver_state_t system_led_init(system_led_t* v_sled, driver_mcu_t* v_dmcu);
 driver_state_t system_led_set(system_led_t* v_sled, driver_mcu_t* v_dmcu, system_led_event_t v_sled_event);

#endif // __SYSTEM_LED_H

/* End of file -------------------------------------------------------- */
