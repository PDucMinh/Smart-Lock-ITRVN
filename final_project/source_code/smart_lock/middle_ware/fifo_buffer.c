/**
 * @file       fifo_buffer.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    
 * @version    1.0.0
 * @date       2024-08-04
 * @author     Minh Pham
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
static uint8_t fifo_pool[FIFO_MAX_NUM][FIFO_MAX_SIZE];
static uint8_t fifo_index = 0;
/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
void fifo_init(fifo_buffer_info_t* fifo_buffer, uint16_t fifo_size, uint32_t info_size)
{
  if (((fifo_size * info_size) > FIFO_MAX_SIZE) || (fifo_size == 0) || (info_size == 0))
  {
    return;
  }
  if (fifo_buffer == NULL)
  {
    return;
  }
  if (fifo_index == FIFO_MAX_NUM)
  {
    return;
  }
  fifo_buffer->fifo_size = fifo_size;
  fifo_buffer->info_size = info_size;
  fifo_buffer->pbuf = *fifo_pool + fifo_index;
  fifo_index = fifo_index + 1;
  fifo_buffer->tail = 0;
}

void fifo_empty(fifo_buffer_info_t *fifo_buffer)
{
  if (fifo_buffer->tail == 0)
  {
    return;
  }
  fifo_buffer->tail = 0;
}

fifo_return_t fifo_push(fifo_buffer_info_t* fifo_buffer, void* source_data)
{
  if (fifo_buffer == NULL)
  {
    return FIFO_FAIL;
  }
  else if (source_data == NULL)
  {
    return FIFO_FAIL;
  }
  else if (fifo_buffer->tail > (fifo_buffer->fifo_size))
  {
    return FIFO_FAIL;
  }
  else
  {
    uint8_t* temp_pbuf = fifo_buffer->pbuf + (fifo_buffer->tail)*(fifo_buffer->info_size);
    memcpy((void *)temp_pbuf, source_data, fifo_buffer->info_size);
    fifo_buffer->tail = fifo_buffer->tail + 1;
  }
  return FIFO_OK;
}

fifo_return_t fifo_pop(fifo_buffer_info_t* fifo_buffer, void* dest_data)
{
  if (fifo_buffer == NULL)
  {
    return FIFO_FAIL;
  }
  else if (dest_data == NULL)
  {
    return FIFO_FAIL;
  }
  if (fifo_buffer->tail == 0)
  {
    return FIFO_FAIL;
  }
  else
  {
    uint8_t* temp_pbuf = fifo_buffer->pbuf;
    memcpy(dest_data,(void *)temp_pbuf, fifo_buffer->info_size);
    for (uint16_t i = 0; i < fifo_buffer->fifo_size; i++)
    {
      memmove((void *)temp_pbuf, (void *)(temp_pbuf + fifo_buffer->info_size), fifo_buffer->info_size);
      temp_pbuf = temp_pbuf + fifo_buffer->info_size;
    }
    fifo_buffer->tail = fifo_buffer->tail - 1;
  }
  return FIFO_OK;
}

uint8_t fifo_size(fifo_buffer_info_t *fifo_buffer)
{
  return fifo_buffer->tail + 1;
}
/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
