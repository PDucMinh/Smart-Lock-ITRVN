/**
 * @file       fifo_buffer.c
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
#include "fifo_buffer.h"

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
fifo_return_t fifo_set_head(fifo_buffer_info_t *fifo_buffer, uint8_t head);

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
fifo_return_t fifo_set_tail(fifo_buffer_info_t *fifo_buffer, uint8_t tail);

/* Function definitions ----------------------------------------------- */
void fifo_init(fifo_buffer_info_t *fifo_buffer, uint32_t fifo_size)
{
  if ((fifo_size > FIFO_MAX_SIZE) || (fifo_size == 0))
  {
    return;
  }
  fifo_buffer->fifo_size = fifo_size;
  fifo_set_head(fifo_buffer, 0);
  fifo_set_tail(fifo_buffer, 0);
}

void fifo_empty(fifo_buffer_info_t *fifo_buffer)
{
  if (fifo_buffer->head == fifo_buffer->tail)
  {
    return;
  }
  fifo_set_head(fifo_buffer, 0);
  fifo_set_tail(fifo_buffer, 0);
  // something
}

uint8_t fifo_push(fifo_buffer_info_t *fifo_buffer, fifo_buffer_info_t *source_data)
{
  if (fifo_buffer->tail >= fifo_buffer->size)
  {
    return FIFO_FAIL;
  }
  else 
  {
    fifo_buffer_info_t *temp_buffer = fifo_buffer;
    temp_buffer = temp_buffer + fifo_buffer->tail;
    temp_buffer = source_data;
    fifo_buffer->tail = fifo_buffer->tail + 1;
    fifo_set_tail(fifo_buffer, fifo_buffer->tail);
  }
  // something
}

uint8_t fifo_pop(fifo_buffer_info_t *fifo_buffer, void *dest_data)
{
}

uint8_t fifo_size(fifo_buffer_info_t *fifo_buffer)
{
}
/* Private definitions ----------------------------------------------- */
fifo_return_t fifo_set_head(fifo_buffer_info_t *fifo_buffer, uint8_t head)
{
  if (head != 0)
  {
    return FIFO_FAIL;
  }
  for (uint16_t i = 0; i < fifo_buffer->fifo_size; i++)
  {
    fifo_buffer->head = head;
  }
  return FIFO_OK;
}

fifo_return_t fifo_set_tail(fifo_buffer_info_t *fifo_buffer, uint8_t tail)
{
  if (tail < 0)
  {
    return FIFO_FAIL;
  }
  if (tail > fifo_buffer->fifo_size)
  {
    tail = 0;
  }
  for (uint16_t i = 0; i < fifo_buffer->fifo_size; i++)
  {
    fifo_buffer->tail = tail;
  }
  return FIFO_OK;
}
/* End of file -------------------------------------------------------- */
