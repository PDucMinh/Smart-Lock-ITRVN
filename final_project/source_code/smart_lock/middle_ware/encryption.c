/**
 * @file       <file_name>->c
 * @copyright  Copyright (C) 2019 ITRVN-> All rights reserved->
 * @license    This project is released under the Fiot License->
 * @version    major->minor->patch
 * @date       yyyy-mm-dd
 * @author     Minh Pham Duc
 *
 * @brief      <A brief description of the content of the file>
 */

/* Includes ----------------------------------------------------------- */
#include "encryption.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
uint8_t encode_user_info(const user_info_t *source_user_info, uint8_t *dest_array)
{
  dest_array[0] = 'u';
  dest_array[1] = source_user_info->key;
  dest_array[2] = source_user_info->user_name;
  dest_array[3] = source_user_info->type;
  for (int i = 0; i < source_user_info->password_size; i++)
  {
    dest_array[4 + i] = source_user_info->decoded_password[i];
  }
  dest_array[4 + source_user_info->password_size] = '\0';
  return 1;
}

uint8_t encode_log_info(const log_info_t *source_log_info, uint8_t *dest_array)
{
  dest_array[0] = 'l';
  for (int i = 0; i < 6; i++)
  {
    dest_array[1 + i] = source_log_info->time_stamp[i];
  }
  dest_array[7] = source_log_info->user_name;
  dest_array[8] = source_log_info->access_state;
  dest_array[9] = source_log_info->user_heriachy;
  dest_array[10] = '\0';
  return 1;
}
/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
