/**
 * @file       <file_name>.c
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

/* Includes ----------------------------------------------------------- */
#include "encryption.h"

/* Private defines ---------------------------------------------------- */
#define MAX_ENCODED_STRING_SIZE 150
/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */
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
static void private_function(void);
/* Function definitions ----------------------------------------------- */
char *encode_string(const char *string)
{
  int len = str_len(string);
  char encoded[MAX_ENCODED_STRING_SIZE];
  sprintf(encoded, "%d:%s", len, string);
  return encoded;
}

char *encode_number(const int *number)
{
  char encoded[MAX_ENCODED_STRING_SIZE];
  sprintf(encoded, "i%de", number);
  return encoded;
}

char *encode_log_info(log_info_t *log_info)
{
  char time[MAX_ENCODED_STRING_SIZE];
  char encoded[MAX_ENCODED_STRING_SIZE];
  for (int i = 0; i < 6; i++)
  {
    strcat(time, encode_number(log_info->time_stamp[i]));
  }
  sprintf(encoded,
          "%s%s%s%s",
          time,
          encode_string(log_info->user_name),
          encode_string(log_info->access),
          encode_string(log_info->user_hierarchy));
  return encoded;
}

int str_len(char *str)
{
  int len = 0;
  for (len; str[len] != '\0'; len++);
  return len;
}
/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
