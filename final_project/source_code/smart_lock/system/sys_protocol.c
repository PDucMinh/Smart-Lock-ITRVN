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
  for (int i = 0; *(src_data_string + 8 + data_f.length * 2 + i * 2) != '\0'; i++)
  {
    sscanf(src_data_string + 8 + data_f.length * 2 + i * 2, "%2hhx%*x", &temp);
    data_f.crc[i] = temp;
  }
  dest_data_frame->header = data_f.header;
  dest_data_frame->sequence = data_f.sequence;
  dest_data_frame->command = data_f.command;
  dest_data_frame->length = data_f.length;
  for (int i = 0; i < MAX_DATA_LENGTH; i++)
    dest_data_frame->data[i] = data_f.data[i];
  for (int i = 0; i < MAX_CRC_LENGTH; i++)
    dest_data_frame->crc[i] = data_f.crc[i];
}

char write_data_frame_to_string(data_frame_t *src_data_frame)
{
}

void sys_protocol_loop(/*something here*/)
{
}
/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
