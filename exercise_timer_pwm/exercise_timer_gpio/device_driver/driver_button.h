/**
 * @file       driver_button.h
 * @copyright
 * @license
 * @version
 * @date       2024-07-07
 * @author     Hung Nguyen Nhat
 *
 * @brief      This file export the following functions:
 *             - driver_button_init : Initializing GPIO pin for button
 *             - driver_button_read : Reading button state
 * @note
 * @example
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __DRIVER_BUTTON_H
#define __DRIVER_BUTTON_H

/* Includes ----------------------------------------------------------- */
#include "driver_mcu.h"
#include "driver.h"
/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief status of button
 */
typedef enum
{
  DRIVER_BUTTON_STATE_IS_PUSHED, /**< Button is pushed */
  DRIVER_BUTTON_STATE_NO_PUSHED, /**< Button is not pushed */
  DRIVER_BUTTON_STATE_NO_READ    /**< GPIO pin is not allowed to read */
} driver_button_state_t;

/**
 * @brief type of button
 */
typedef enum
{
  DRIVER_BUTTON_TYPE_PU, /**< button is connected with pull-up register */
  DRIVER_BUTTON_TYPE_PD  /**< button is connected with pull-down register */
} driver_button_type_t;

/**
 * @brief struct manage properties of button
 */
typedef struct
{
  driver_button_type_t button_type; /**< type of button */
  driver_mcu_pin_t button_io;       /**<GPIO pin used for button */
  GPIO_PinState button_io_preState; /**<previous GPIO status */
  uint32_t button_tick;             /**< the tick read from Systick counter when start debouncing */
} driver_button_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief  Initialize GPIO pin to be used for button
 *
 * @param[in]     dbutton  <struct pointer managing the button>
 *
 * @attention
 *
 * @return
 *  - DRIVER_PASS: the button is initialized successfully
 *  - DRIVER_FAIL: the button is initialized fail
 */
driver_state_t driver_button_init(driver_button_t* dbutton);

/**
 * @brief  reading button state
 *
 * @param[in]     dbutton  <struct pointer managing the button>
 *
 * @attention
 *
 * @return
 *  - DRIVER_BUTTON_NO_PUSHED: the button is not pushed
 *  - DRIVER_BUTTON_IS_PUSHED: the button is pushed
 */
driver_button_state_t driver_button_read(driver_button_t* dbutton);

#endif // __DRIVER_BUTTON_H

/* End of file -------------------------------------------------------- */
