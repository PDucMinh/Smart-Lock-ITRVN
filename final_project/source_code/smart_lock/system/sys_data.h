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
#include "fifo_buffer.h"
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
  SYS_DATA_FEEDBACK_ACK,
  SYS_DATA_FEEDBACK_NACK,  /**< Description of PUBLIC_ENUM_1 */
  SYS_DATA_FEEDBACK_DONE, /**< Description of PUBLIC_ENUM_2 */
  SYS_DATA_FEEDBACK_EXECUTING,     /**< Description of PUBLIC_ENUM_3 */
} sys_data_feedback_t;

/**
 * @brief <enum descriptiton>
 */
typedef enum
{
  SYS_DATA_REQ_NONE,
  SYS_DATA_REQ_NOTIFY_ALARM, /**< Description of PUBLIC_ENUM_1 */
  SYS_DATA_REQ_NOTIFY_DOUBLE_LOCK,
  SYS_DATA_REQ_NOTIFY_OPEN,
  SYS_DATA_REQ_NOTIFY_RIGHT_PASS,
  SYS_DATA_REQ_NOTIFY_WRONG_PASS,
  SYS_DATA_REQ_DISPLAY,
  SYS_DATA_REQ_LOG_SET_ACCESS_TIME, /**< Description of PUBLIC_ENUM_3 */
  SYS_DATA_REQ_LOG_LOAD_USER_INFO,
  SYS_DATA_REQ_LOG_SET_USER_INFO,
  SYS_DATA_REQ_LOG_LOAD_ACCESS_TIME,
  SYS_DATA_REQ_LOCK_OPEN,
  SYS_DATA_REQ_LOCK_CLOSE,
  SYS_DATA_REQ_LOCK_DOUBLE_LOCK,
} sys_data_req_t;

/**
 * @brief <structure descriptiton>
 */
typedef union
{
  struct 
  {
    sys_data_req_t req;
    uint8_t* pdata;
    uint32_t data_size;
  } info;
  sys_data_req_t req;
  sys_data_feedback_t ret;
} sys_data_t;

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
sys_data_status_t sys_data_add(sys_data_t* data, fifo_buffer_info_t* buf_info);

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
sys_data_t sys_data_get(fifo_buffer_info_t* buf_info);
#endif // __SYS_DATA_H

/* End of file -------------------------------------------------------- */
