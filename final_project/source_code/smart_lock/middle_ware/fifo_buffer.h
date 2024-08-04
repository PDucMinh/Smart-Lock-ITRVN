/**
 * @file       fifo_buffer.h
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
#ifndef __FIFO_BUFFER_H
#define __FIFO_BUFFER_H

/* Includes ----------------------------------------------------------- */
#include <stdio.h>
/* Public defines ----------------------------------------------------- */
#define FIFO_MAX_SIZE (100) /* MAX OF FIFO SIZE */
#define FIFO_MAX_NUM  (10)
/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief return message of fifo buffer
 */
typedef enum
{
  FIFO_OK,
  FIFO_FAIL
} fifo_return_t;

/**
 * @brief declare fifo buffer structure
 */
typedef struct
{
  uint8_t* pbuf;
  uint32_t fifo_size; // max size of sub fifo
  uint32_t info_size;
  uint8_t tail; // tail <= size aka tail = next empty slot
} fifo_buffer_info_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief  initialize blank fifo buffer
 *
 * @param[in]     <param_name>  <param_despcription>
 * @param[in]    <param_name>  <param_despcription>
 * @param[inout]  <param_name>  <param_despcription>
 *
 * @attention  <API attention note>
 *
 * @return     
 *  
 */
void fifo_init(fifo_buffer_info_t* fifo_buffer, uint16_t fifo_size, uint32_t info_size);

/**
 * @brief  clear fifo buffer
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
void fifo_empty(fifo_buffer_info_t *fifo_buffer);

/**
 * @brief  add new data to fifo buffer
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
fifo_return_t fifo_push(fifo_buffer_info_t* fifo_buffer, void* source_data);

/**
 * @brief  get data from fifo buffer and delete it
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
fifo_return_t fifo_pop(fifo_buffer_info_t *fifo_buffer, fifo_buffer_info_t *dest_data);

/**
 * @brief  get activated size of fifo buffer
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
uint8_t fifo_size(fifo_buffer_info_t *fifo_buffer);
#endif // __CODE_TEMPLATE_H

/* End of file -------------------------------------------------------- */
