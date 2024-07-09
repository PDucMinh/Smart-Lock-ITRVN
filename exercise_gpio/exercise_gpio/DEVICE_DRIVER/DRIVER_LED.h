/**
 * @file       DRIVER_LED.h
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
#include "DRIVER_MCU.h"
#include "DRIVER.h"
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief state ID of led for turning on and turning off led
 */
typedef enum
{
  DRIVER_LED_ON,  /**< State led is on */
  DRIVER_LED_OFF, /**< State led is off */
} driver_led_set_t;

/**
 * @brief the type of led
 */
typedef enum
{
  DRIVER_LED_ACOMMON, /**< led is common anode type */
  DRIVER_LED_KCOMMON, /**< led is common katode type */
} driver_led_type_t;

/**
 * @brief struct manage properties of led
 */
typedef struct
{
  driver_led_type_t led_type; /**< Description of member_2 */
  uint16_t led_io;            /**< Description of member_3 */
} driver_led_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief  Initialize GPIO pin to be used for for
 *
 * @param[in]     dl  <struct pointer managing the led>
 *
 * @attention
 *
 * @return
 *  - DRIVER_PASS: the led is initialized successfully
 *  - DRIVER_FAIL: the led is initialized fail
 */
driver_state_t driver_led_init(driver_led_t* dl);

/**
 * @brief  setting led state
 *
 * @param[in]     dl  <struct pointer managing the led>
 * @param[out]    state <the state of led>
 *
 * @attention
 *
 * @return
 *  - DRIVER_PASS: the led is set successfully
 *  - DRIVER_FAIL: the led is set fail
 */
driver_state_t driver_led_set(driver_led_t* dl, driver_led_set_t state);

#endif // __DRIVER_LED_H

/* End of file -------------------------------------------------------- */
