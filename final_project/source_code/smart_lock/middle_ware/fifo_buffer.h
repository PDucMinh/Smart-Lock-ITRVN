/**
 * @file       fifo_buffer.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license
 * @version    1.0.0
 * @date       2024-08-04
 * @author     Minh Pham
 *
 * @brief      <A brief description of the content of the file>
 *
 * @note
 * @example
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __FIFO_BUFFER_H
#define __FIFO_BUFFER_H

/* Includes ----------------------------------------------------------- */
#include <stdio.h>
/* Public defines ----------------------------------------------------- */
#define FIFO_MAX_SIZE (100) /* MAX OF FIFO SIZE */
#define FIFO_MAX_NUM (10)
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
 * @param[in]      info_size    <size of a data item>
 * @param[in]      fifo_size    <number of data item inside fifo>
 * @param[inout]   fifo_buffer  <struct pointer to a fifo buffer>
 *
 * @attention  <API attention note>
 *
 * @return     none
 *
 */
void fifo_init(fifo_buffer_info_t* fifo_buffer, uint16_t fifo_size, uint32_t info_size);

/**
 * @brief  clear fifo buffer
 *
 * @param[inout]  fifo_buffer  <struct pointer to fifo buffer>
 *
 * @attention  <API attention note>
 *
 * @return     none
 *
 */
void fifo_empty(fifo_buffer_info_t* fifo_buffer);

/**
 * @brief  add new item data to fifo buffer
 *
 * @param[in]     source_data  <pointer to source data buffer>
 * @param[inout]  fifo_buffer  <struct pointer to fifo buffer>
 *
 * @attention  <API attention note>
 *
 * @return
 *  - 0: FIFO_OK
 *  - 1: FIFO_FAIL
 */
fifo_return_t fifo_push(fifo_buffer_info_t* fifo_buffer, void* source_data);

/**
 * @brief  get data from fifo buffer and delete it
 *
 * @param[in]     dest_data    <pointer to data buffer receive item from fifo>
 * @param[inout]  fifo_buffer  <struct pointer to fifo buffer>
 *
 * @attention  <API attention note>
 *
 * @return
 *  - 0: FIFO_OK
 *  - 1: FIFO_FAIL
 */
fifo_return_t fifo_pop(fifo_buffer_info_t* fifo_buffer, fifo_buffer_info_t* dest_data);

/**
 * @brief  get activated size of fifo buffer
 *
 * @param[inout]  fifo_buffer  <struct pointer to fifo buffer>
 *
 * @attention  <API attention note>
 *
 * @return     number of item inside a fifo
 *  
 */
uint8_t fifo_size(fifo_buffer_info_t* fifo_buffer);
#endif // __FIFO_BUFFER_H

/* End of file -------------------------------------------------------- */
