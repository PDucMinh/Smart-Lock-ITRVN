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
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief define user information structure
 */
typedef struct
{
    char *key;
    int rfid;
    char *user_name;
    char *encoded_password;
    char *type;
} user_info_t;

/**
 * @brief define log structure before encoded to send to UI
 */
typedef struct
{
    int time_stamp[6];
    char *user_name;
    char *access;
    char *user_hierarchy;
} log_info_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  bencode encoding string
 *
 * @param[in]     string  array of characters
 * @param[out]    encoded_string array of encoded string
 *
 * @attention  <API attention note>
 *
 * @return  
 *  - 0: Error
 *  - <size>:<string> : encoded string
 */
char *encode_string(const char *string);

/**
 * @brief  bencode encoding integer number
 *
 * @param[in]     number array of integer
 * @param[out]    encoded_number array of string contain encoded number 
 *
 * @attention  <API attention note>
 *
 * @return  
 *  - 0: Error
 *  - i<number>e : Encoded number
 */
char *encode_number(const int *number);

/**
 * @brief  bencode encoding log information
 *
 * @attention  <API attention note>
 *
 * @return  
 *  - 0: Error
 *  - l<data>e : Encoded log information
 */
char *encode_log_info(const log_info_t *log_info);

/**
 * @brief  count string length
 *
 * @param[in]     str array of character
 * @param[out]    str_len length of string
 *
 * @attention  <API attention note>
 *
 * @return  
 */
int str_len(const char *str);

/**
 * @brief  decode string to number
 *
 * @param[in]     str array of character
 * @param[out]    decode_number number after decode
 *
 * @attention  <API attention note>
 *
 * @return  
 */
int decode_number(const char *str);


#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
