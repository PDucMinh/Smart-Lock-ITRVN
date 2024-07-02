/**
 * @file       <file_name>.c
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
#include "cbuffer.h"

/* Private defines ---------------------------------------------------- */
// #define PRIVATE_DEFINE_1  (0) /*!< Description of PRIVATE_DEFINE_1 */
// #define PRIVATE_DEFINE_2  (0) /*!< Description of PRIVATE_DEFINE_2 */
/* Private enumerate/structure ---------------------------------------- */
/**
 * @brief <enum descriptiton>
 */
// typedef enum 
// {
//   PRIVATE_ENUM_1, /**< Description of PRIVATE_ENUM_1 */
//   PRIVATE_ENUM_2, /**< Description of PRIVATE_ENUM_2 */
//   PRIVATE_ENUM_3  /**< Description of PRIVATE_ENUM_3 */
// }
// private_enum_type_t;

/**
 * @brief <structure descriptiton>
 */
// typedef struct 
// {
//   uint32_t member_1, /**< Description of member_1 */
//   uint32_t member_2, /**< Description of member_2 */
//   uint32_t member_3  /**< Description of member_3 */
// }
// private_struct_type_t;

/* Private macros ----------------------------------------------------- */
/**
 * @brief  <macro description>
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
// #define PRIVATE_MACRO(a)  do_something_with(a)
#define CHECK(A,B) return B

/* Public variables --------------------------------------------------- */
// int g_var_1;
// int g_var_2;

/* Private variables -------------------------------------------------- */
// static int var_1; /**< Description of private variable var_1 */
// static int var_2; /**< Description of private variable var_2 */

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
void cb_init(cbuffer_t *cb, void *buf, uint32_t size)
{
  if (size == 0)
  {
    return;
  }

  cb->data = (uint8_t *)malloc(size);
  memset(cb->data, 0, size);

  if (buf != NULL)
  {
    memmove(cb->data, buf, size);
  }

  cb->size = size;
  cb->writer = 0;
  cb->reader = 0;
  cb->overflow = 0;
  cb->active = true;
}

void cb_clear(cbuffer_t *cb)
{
  if (cb == NULL)
  {
    return;
  }
  memset(cb->data, 0, cb->size);
  cb->writer = 0;
  cb->reader = 0;
  cb->overflow = 0;
}
uint32_t cb_write(cbuffer_t *cb, void *buf, uint32_t nbytes)
{
  uint32_t index;
  uint8_t *tmp;
  if ((cb != NULL) && (buf != NULL) && (cb->overflow == false))
  {
    for (index = 0; index < nbytes; index++)
    {
      if ((cb->reader) == 0)
        if ((cb->writer) == (cb->size - 1))
        {
          cb->overflow = cb->overflow + 1;
        }
        else if ((cb->writer + 1) == cb->reader)
        {
          cb->overflow = cb->overflow + 1;
        }
      tmp = (uint8_t *)buf;
      *(cb->data + cb->writer) = *tmp;
      cb->writer = cb->writer + 1;
      if ((cb->writer) == (cb->size))
        cb->writer = 0;
    }
    return index;
  }
}
uint32_t cb_read(cbuffer_t *cb, void *buf, uint32_t nbytes)
{
  uint32_t index;
  uint8_t *tmp;
  if ((cb != NULL) && (buf != NULL))
  {
    for (index = 0; index < nbytes; index++)
    {
      if ((cb->reader) == (cb->writer))
        break;
      tmp = (uint8_t *)buf;
      *tmp = *(cb->data + cb->reader);
      cb->reader = cb->reader + 1;
      if ((cb->reader) == (cb->size))
        cb->reader = 0;
    }
    return index;
  }
}
