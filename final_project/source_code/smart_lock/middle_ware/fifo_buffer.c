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
#define CHECK_SIZE(A) \
  do                 \
  {                  \
    if (A > FIFO_MAX_SIZE) \
    {                \
      return FIFO_FAIL; \
    }                \
    else if (A == 0) \
    {                \
      return FIFO_FAIL; \
    }                \
  } while (0)
  
#define CHECK_NULL(A) \
  do                 \
  {                  \
    if (A <= 0)   \
    {                \
      return FIFO_FAIL; \
    }                \
  } while (0)
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
fifo_return_t fifo_set_front(fifo_buffer_info_t *fifo_buffer, uint8_t front);

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
fifo_return_t fifo_set_rear(fifo_buffer_info_t *fifo_buffer, uint8_t rear);

/* Function definitions ----------------------------------------------- */
void fifo_init(fifo_buffer_info_t *fifo_buffer, uint32_t fifo_size)
{
  CHECK_SIZE(fifo_size);
  fifo_buffer->fifo_size = fifo_size;
  fifo_set_front(fifo_buffer, 0);
  fifo_set_rear(fifo_buffer, 0);
}

void fifo_empty(fifo_buffer_info_t *fifo_buffer)
{
  CHECK_NULL(fifo_buffer->rear - fifo_buffer->front);
  fifo_set_front(fifo_buffer, 0);
  fifo_set_rear(fifo_buffer, 0);
  //something
}

uint8_t fifo_push(fifo_buffer_info_t *fifo_buffer, void *source_data)
{

}

uint8_t fifo_pop(fifo_buffer_info_t *fifo_buffer, void *dest_data)
{

}

uint8_t fifo_size(fifo_buffer_info_t *fifo_buffer)
{

}
/* Private definitions ----------------------------------------------- */
fifo_return_t fifo_set_front(fifo_buffer_info_t *fifo_buffer, uint8_t front)
{
  for (uint16_t i = 0; i < fifo_buffer->fifo_size; i++)
  {
    fifo_buffer->front = front;
  }
  return FIFO_OK;
}

fifo_return_t fifo_set_rear(fifo_buffer_info_t *fifo_buffer, uint8_t rear)
{
  for (uint16_t i = 0; i < fifo_buffer->fifo_size; i++)
  {
    fifo_buffer->rear = rear;
  }
  return FIFO_OK;
} 
/* End of file -------------------------------------------------------- */
