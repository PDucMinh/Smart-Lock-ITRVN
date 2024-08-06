/**
 * @file       <file_name>.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    major.minor.patch
 * @date       yyyy-mm-dd
 * @author     <first_name_1> <last_name_1>
 * @author     <first_name_2> <last_name_2>
 *             
 * @brief      <A brief description of the content of the file>
 *             
 * @note          
 * @example    example_file_1.c
 *             Example_1 description
 * @example    example_file_2.c
 *             Example_2 description
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
 *  - Others: Encoded string
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
 *  - Others: Encoded number
 */
char *encode_number(const int *number);

/**
 * @brief  bencode encoding log information
 *
 * @attention  <API attention note>
 *
 * @return  
 *  - 0: Error
 *  - Others: Encoded log information
 */
char *encode_log_info(log_info_t *log_info);

/**
 * @brief  <function description>
 *
 * @param[in]     str array of character
 * @param[out]    str_len length of string
 *
 * @attention  <API attention note>
 *
 * @return  
 */
int str_len(char *str);


#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
