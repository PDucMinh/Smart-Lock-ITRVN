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
#include "bsp_uart.h"
#include "fifo_buffer.h"
#include "sys_data.h"
/* Public defines ----------------------------------------------------- */

// #define ALLOW_CRC
#define MAX_DATA_LENGTH 100

#ifdef ALLOW_CRC
#define MAX_CRC_LENGTH 4
#define HALF_MAX_CRC_LENGTH 2
#else
#define MAX_CRC_LENGTH 0
#define HALF_MAX_CRC_LENGTH 0
#endif

#define MAX_FRAME_LENGTH ((MAX_DATA_LENGTH + MAX_CRC_LENGTH + 8) * 2)

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

  #ifdef ALLOW_CRC
  uint8_t crc[MAX_CRC_LENGTH];
  #endif

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
void read_data_frame_from_uint8_array(data_frame_t *dest_data_frame, uint8_t *src_data_array);

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
void write_data_frame_to_uint8_array(data_frame_t *src_data_frame, uint8_t *dest_data_array);

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
void sys_protocol_loop(fifo_buffer_info_t *fifo_request);

#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
