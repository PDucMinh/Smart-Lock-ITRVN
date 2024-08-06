/**
 * @file       sys_protocol.h
 * @copyright  Copyright (C). All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    major.minor.patch
 * @date       yyyy-mm-dd
 * @author     Minh Pham Duc
 *
 * @brief      <A brief description of the content of the file>
 *
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __SYS_PROTOCOL_H
#define __SYS_PROTOCOL_H

/* Includes ----------------------------------------------------------- */

/* Public defines ----------------------------------------------------- */
#define MAX_DATA_LENGTH 50
#define MAX_CRC_LENGTH 8
/* Public enumerate/structure ----------------------------------------- */

/**
 * @brief <structure descriptiton>
 */
typedef struct
{
  uint8_t header;
  uint8_t sequence;
  uint8_t command;
  uint8_t length;
  uint8_t data[MAX_DATA_LENGTH];
  uint8_t crc[MAX_CRC_LENGTH];
} data_frame_t;

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
void read_data_frame_from_string(data_frame_t *dest_data_frame, char *src_data_string);

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
char write_data_frame_to_string(data_frame_t *src_data_frame);

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
void sys_protocol_loop(/*something here*/);

#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
