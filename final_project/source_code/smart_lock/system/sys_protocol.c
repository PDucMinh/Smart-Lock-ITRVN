/**
 * @file       sys_protocol.c
 * @copyright  Copyright (C). All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    major.minor.patch
 * @date       yyyy-mm-dd
 * @author     Minh Pham Duc
 *
 * @brief      <A brief description of the content of the file>
 *
 */

/* Includes ----------------------------------------------------------- */
#include "sys_protocol.h"

/* Private defines ---------------------------------------------------- */

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
void read_data_frame_from_string(data_frame_t *dest_data_frame, char *src_data_string)
{
  data_frame_t data_f;

  // First sscanf call to parse header, sequence, command, and length
  int result1 = sscanf(src_data_string,
                       "%2hhx%2hhx%2hhx%2hhx%*x",
                       &data_f.header,
                       &data_f.sequence,
                       &data_f.command,
                       &data_f.length);

  // Check if the first parsing was successful
  // Second sscanf call to parse data and CRC based on the length
  uint8_t temp;
  for (int i = 0; i < data_f.length; i++)
  {
    sscanf(src_data_string + 8 + i * 2, "%2hhx%*x", &temp);
    data_f.data[i] = temp;
  }

  #ifdef ALLOW_CRC
  for (int i = 0; *(src_data_string + 8 + data_f.length * 2 + i * 2) != '\0'; i++)
  {
    sscanf(src_data_string + 8 + data_f.length * 2 + i * 2, "%2hhx%*x", &temp);
    data_f.crc[i] = temp;
  }
  #endif

  dest_data_frame->header = data_f.header;
  dest_data_frame->sequence = data_f.sequence;
  dest_data_frame->command = data_f.command;
  dest_data_frame->length = data_f.length;
  for (int i = 0; i < data_f.length; i++)
    dest_data_frame->data[i] = data_f.data[i];

  #ifdef ALLOW_CRC
  for (int i = 0; i < MAX_CRC_LENGTH; i++)
    dest_data_frame->crc[i] = data_f.crc[i];
  #endif
}

char write_data_frame_to_string(data_frame_t *src_data_frame)
{
  char data_string[MAX_FRAME_LENGTH];
  sprintf(data_string, "%02x%02x%02x%02x", src_data_frame->header, src_data_frame->sequence, src_data_frame->command, src_data_frame->length);
  
  char frame_temp[MAX_DATA_LENGTH];
  for (int i=0; i<src_data_frame->length; i++)
  {
    sprintf(frame_temp, "%02x", src_data_frame->data[i]);
    strcat(data_string, frame_temp);
  }

  #ifdef ALLOW_CRC
  char crc_temp[MAX_CRC_LENGTH];
  for (int i=0; i<HALF_MAX_CRC_LENGTH; i++)
  {
    sprintf(crc_temp, "%02x", src_data_frame->crc[i]);
    strcat(data_string, crc_temp);
  }
  #endif
  
  return data_string;
}

void sys_protocol_loop(/*something here*/)
{
}
/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
