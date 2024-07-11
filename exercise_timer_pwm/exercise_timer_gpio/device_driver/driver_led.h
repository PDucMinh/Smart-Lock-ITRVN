/**
 * @file       driver_led.h
 * @copyright
 * @license
 * @version
 * @date       2024-07-07
 * @author     Hung Nguyen Nhat
 *
 * @brief      This file export the following functions:
 *             - driver_led_init : Initializing GPIO pin for led
 *             - driver_led_read : Setting led state
 *
 * @note
 * @example
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __DRIVER_LED_H
#define __DRIVER_LED_H

/* Includes ----------------------------------------------------------- */
#include "driver_mcu.h"
#include "driver.h"
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief state ID of led for turning on and turning off led
 */
typedef enum
{
  DRIVER_LED_STATE_ON,  /**< State led is on */
  DRIVER_LED_STATE_OFF, /**< State led is off */
  DRIVER_LED_STATE_BLINK
} driver_led_state_t;

/**
 * @brief the type of led
 */
typedef enum
{
  DRIVER_LED_TYPE_ACOMMON, /**< led is common anode type */
  DRIVER_LED_TYPE_KCOMMON, /**< led is common katode type */
} driver_led_type_t;

/**
 * @brief struct manage properties of led
 */
typedef struct
{
  driver_led_type_t led_type; /**< Description of member_2 */
  driver_mcu_pin_t led_pin;   /**< Description of member_3 */
} driver_led_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief  Initialize GPIO pin to be used for for
 *
 * @param[in]     v_dled  <struct pointer managing the led>
 * @param[in]     v_dmcu  <struct pointer managing the MCU peripheral>
 * @attention
 *
 * @return
 *  - DRIVER_PASS: the led is initialized successfully
 *  - DRIVER_FAIL: the led is initialized fail
 */
driver_state_t driver_led_init(driver_led_t* v_dled, driver_mcu_t* v_dmcu);

/**
 * @brief  setting led state
 *
 * @param[in]     v_dled  <struct pointer managing the led>
 * @param[in]     v_dled_state <the state of led>
 * @param[in]     v_dmcu <struc pointer managing MCU peripheral>
 *
 * @attention
 *
 * @return
 *  - DRIVER_PASS: the led is set successfully
 *  - DRIVER_FAIL: the led is set fail
 */
driver_state_t driver_led_set(driver_mcu_t* v_dmcu, driver_led_t* v_dled, driver_led_state_t v_dled_state);

#endif // __DRIVER_LED_H

/* End of file -------------------------------------------------------- */
