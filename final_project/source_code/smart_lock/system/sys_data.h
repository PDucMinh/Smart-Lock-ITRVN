/**
 * @file       sys_data.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license
 * @version    1.0.0
 * @date       2024-08-04
 * @author     Hung Nguyen
 *
 * @brief      <A brief description of the content of the file>
 *
 * @note
 * @example
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __SYS_DATA_H
#define __SYS_DATA_H

/* Includes ----------------------------------------------------------- */
#include "stm32f4xx_hal.h"
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */

/**
 * @brief <enum descriptiton>
 */
typedef enum
{
  SYS_DATA_STATUS_FAIL,    /**< Description of PUBLIC_ENUM_1 */
  SYS_DATA_STATUS_SUCCESS, /**< Description of PUBLIC_ENUM_2 */
} sys_data_status_t;

/**
 * @brief <enum descriptiton>
 */
typedef enum
{
  SYS_EVENT_NONE,
  SYS_EVENT_KEYPAD_1,
  SYS_EVENT_KEYPAD_2,
  SYS_EVENT_KEYPAD_3,
  SYS_EVENT_KEYPAD_4,
  SYS_EVENT_KEYPAD_WAKEUP,   /**< Description of PUBLIC_ENUM_1 */
  SYS_EVENT_KEYPAD_CHAR_DEL, /**< Description of PUBLIC_ENUM_2 */
  SYS_EVENT_KEYPAD_ENTER,    /**< Description of PUBLIC_ENUM_3 */
  SYS_EVENT_DISPLAY_TIMEOUT,
  SYS_EVENT_LOCK_LOCKED,
  SYS_EVENT_LOCK_UNLOCKED,
  SYS_EVENT_LOCK_ALARM,
  SYS_EVENT_LOCK_DOUBLE_LOCKED,
  SYS_EVENT_LOG_ALL_USER,
  SYS_EVENT_LOG_ALL,
  SYS_EVENT_LOG_ADMIN,
  SYS_EVENT_LOG_SET_COMPLETE,
  SYS_EVENT_PROTOCOL_SEND,
  SYS_EVENT_PROTOCOL_RECEIVE,
  SYS_EVENT_PROTOCOL_COMPLETE
} sys_event_t;

/**
 * @brief <enum descriptiton>
 */
typedef enum
{
  SYS_REQ_NONE,
  SYS_REQ_KEYPAD_SLEEP,
  SYS_REQ_KEYPAD_MENU,
  SYS_REQ_KEYPAD_PASSWORD,
  SYS_REQ_KEYPAD_RETRY,
  SYS_REQ_NOTIFY_ALARM,
  SYS_REQ_NOTIFY_DOUBLE_LOCK,
  SYS_REQ_NOTIFY_LOCK,
  SYS_REQ_NOTIFY_CORRECT,
  SYS_REQ_NOTIFY_INCORRECT,
  SYS_REQ_NOTIFY_OFF,
  SYS_REQ_DISPLAY_OFF,
  SYS_REQ_DISPLAY_MENU,
  SYS_REQ_DISPLAY_LOCK,
  SYS_REQ_DISPLAY_ENTER_PASSWORD,
  SYS_REQ_DISPLAY_PASSWORD,
  SYS_REQ_DISPLAY_CORRECT,
  SYS_REQ_DISPLAY_INCORRECT,
  SYS_REQ_DISPLAY_BLOCKED,
  SYS_REQ_DISPLAY_SET_COMPLETE,
  SYS_REQ_DISPLAY_TRANSFET_INFO,
  SYS_REQ_LOG_SET_ACCESS,
  SYS_REQ_LOG_SET_USER,
  SYS_REQ_LOG_GET_ALL_USER,
  SYS_REQ_LOG_GET_ALL,
  SYS_REQ_LOG_GET_ADMIN,
  SYS_REQ_LOG_ERASE_USER,
  SYS_REQ_LOG_ERASE_ACCESS,
  SYS_REQ_LOCK_OPEN,
  SYS_REQ_LOCK_CLOSE,
  SYS_REQ_LOCK_DOUBLE_LOCK,
  SYS_REQ_PROTOCOL_ACCEPT_GUI,
  SYS_REQ_PROTOCOL_INFO
} sys_req_t;

/**
 * @brief <structure descriptiton>
 */
typedef struct
{
  struct
  {
    sys_req_t req;
    uint8_t* pdata;
    uint16_t data_size;
  } protocol_req;
  struct
  {
    sys_req_t req;
    uint8_t* pdata;
    uint16_t data_size;
  } log_req;

  sys_req_t notify_req;
  sys_req_t keypad_req;
  sys_req_t display_req;
  struct
  {
    sys_event_t ev;
    uint8_t* pdata;
    uint16_t data_size;
  } protocol_ev;
  struct
  {
    sys_event_t ev;
    uint8_t* pdata;
    uint16_t data_size;
  } log_ev;

  sys_event_t notify_ev;
  sys_event_t keypad_ev;
  sys_event_t display_ev;
} sys_data_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

#endif // __SYS_DATA_H

/* End of file -------------------------------------------------------- */
