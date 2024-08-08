/**
 * @file       <file_name>.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    major.minor.patch
 * @date       yyyy-mm-dd
 * @author     Minh Pham Duc
 *
 * @brief      <A brief description of the content of the file>
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __ENCRYPTION_H
#define __ENCRYPTION_H

/* Includes ----------------------------------------------------------- */
#include "string.h"
#include "stdio.h"
#include "stdint.h"
/* Public defines ----------------------------------------------------- */
#define MAX_PASSWORD_LENGTH 20
#define MAX_ENCODED_STRING_SIZE 150
/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief define user information structure
 */
typedef struct
{
  uint8_t  key; //only from 0-255
  uint8_t user_name; 
  uint8_t type;
  uint8_t password_size; // this will not be encoded to send to UI
  uint8_t decoded_password[MAX_PASSWORD_LENGTH];
} user_info_t;

/**
 * @brief define log structure before encoded to send to UI
 */
typedef struct
{
  uint8_t time_stamp[6];
  uint8_t user_name;
  uint8_t access_state;
  uint8_t user_heriachy;
} log_info_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  bencode encoding string
 *
 * @param[in]     user_info_t
 * @param[out]    uint8_t_array
 *
 * @attention  <API attention note>
 *
 * @return
 *  - 0: Error
 *  - 1: OK
 */
uint8_t encode_user_info(const user_info_t *source_user_info, uint8_t *dest_array);

/**
 * @brief  bencode encoding string
 *
 * @param[in]     log_info_t
 * @param[out]    uint8_t_array
 *
 * @attention  <API attention note>
 *
 * @return
 *  - 0: Error
 *  - 1: OK
 */
uint8_t encode_user_info(const log_info_t *source_log_info, uint8_t *dest_array);

#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
