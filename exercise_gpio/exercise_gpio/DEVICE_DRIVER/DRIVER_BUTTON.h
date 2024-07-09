/**
 * @file       DRIVER_BUTTON.h
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
#include "DRIVER_MCU.h"
#include "DRIVER.h"
/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief status of button
 */
typedef enum
{
  DRIVER_BUTTON_IS_PUSHED, /**< Button is pushed */
  DRIVER_BUTTON_NO_PUSHED, /**< Button is not pushed */
  DRIVER_BUTTON_NO_READ    /**< GPIO pin is not allowed to read */
} driver_button_state_t;

/**
 * @brief type of button
 */
typedef enum
{
  DRIVER_BUTTON_PULL_UP,  /**< button is connected with pull-up register */
  DRIVER_BUTTON_PULL_DOWN /**< button is connected with pull-down register */
} driver_button_type_t;

/**
 * @brief struct manage properties of button
 */
typedef struct
{
  driver_button_type_t button_type; /**< type of button */
  uint16_t button_io;               /**<GPIO pin used for button */
  GPIO_PinState button_io_preState; /**<previous GPIO status */
  uint32_t button_tick;             /**< the tick read from Systick counter when start debouncing */
} driver_button_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief  Initialize GPIO pin to be used for button
 *
 * @param[in]     db  <struct pointer managing the button>
 *
 * @attention
 *
 * @return
 *  - DRIVER_PASS: the button is initialized successfully
 *  - DRIVER_FAIL: the button is initialized fail
 */
driver_state_t driver_button_init(driver_button_t *db);

/**
 * @brief  reading button state
 *
 * @param[in]     db  <struct pointer managing the button>
 * @param[out]    errorCode <pointer to errorCode to store the result of reading process>
 *
 * @attention
 *
 * @return
 *  - DRIVER_BUTTON_NO_PUSHED: the button is not pushed
 *  - DRIVER_BUTTON_IS_PUSHED: the button is pushed
 */
driver_button_state_t driver_button_read(driver_button_t *db, driver_state_t *errorCode);

#endif // __DRIVER_BUTTON_H

/* End of file -------------------------------------------------------- */
