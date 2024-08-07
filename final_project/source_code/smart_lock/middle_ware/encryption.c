/**
 * @file       <file_name>.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    major.minor.patch
 * @date       yyyy-mm-dd
 * @author     Minh Pham Duc
 *
 * @brief      <A brief description of the content of the file>
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

char *encode_log_info(const log_info_t *log_info)
{
  char time[MAX_ENCODED_STRING_SIZE];
  char encoded[MAX_ENCODED_STRING_SIZE];
  for (int i = 0; i < 6; i++)
  {
    strcat(time, encode_number(log_info->time_stamp[i]));
  }
  sprintf(encoded,
          "l%s%s%s%se",
          time,
          encode_string(log_info->user_name),
          encode_string(log_info->access),
          encode_string(log_info->user_hierarchy));
  return encoded;
}
char *encode_user_info(const user_info_t *user_info)
{
  char encoded[MAX_ENCODED_STRING_SIZE];
  sprintf(encoded,
          "u%s%s%s%s%se",
          encode_string(user_info->key),
          encode_number(&user_info->rfid),
          encode_string(user_info->user_name),
          encode_string(user_info->encoded_password),
          encode_string(user_info->type));
}
int str_len(const char *str)
{
  int len = 0;
  for (len; str[len] != '\0'; len++)
    ;
  return len;
}

int decode_number(const char *bencoded_value)
{
  const char *integer_e = strstr(bencoded_value, "e");
  const char *integer_i = strstr(bencoded_value, "i");
  const char *start = integer_i + 1;
  if ((integer_e != 0) && (integer_i != 0))
  {
    int length = (int)(integer_e - integer_i) - 1;
    char decoded_str[MAX_ENCODED_STRING_SIZE];
    strncpy(decoded_str, start, length);
    decoded_str[length] = '\0';
    return atoi(decoded_str);
  }
  else
  {
    return -1;
  }
}
/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
