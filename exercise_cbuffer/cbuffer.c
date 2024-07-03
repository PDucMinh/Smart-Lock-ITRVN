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

#define CHECK_NULL(A, B) \
  do                     \
  {                      \
    if (!A)              \
      return B;          \
  } while (0);
#define CHECK_MAX(A, MAX) \
  do                      \
  {                       \
    if (A > MAX)          \
      return;             \
  } while (0);

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
  CHECK(cb, NULL);
  CHECK(buf, NULL);
  CHECK(size, 0);
  CHECK(size, CB_MAX_SIZE);

  cb->size = size;
  cb->writer = 0;
  cb->reader = 0;
  cb->overflow = 0;
  cb->active = true;
}

void cb_clear(cbuffer_t *cb)
{
  CHECK(cb, NULL);
  cb->writer = 0;
  cb->reader = 0;
  cb->overflow = 0;
}

uint32_t cb_write(cbuffer_t *cb, void *buf, uint32_t nbytes)
{
  CHECK_NULL(cb, NULL);
  CHECK_NULL(buf, NULL);
  uint32_t space_cnt = cb_space_count(cb);
  CHECK_NULL(space_cnt, 0);
  if ((cb->writer) >= (cb->reader))
  {
    int nbytes_tail = 0;
    uint8_t *dst_tail, *src_tail;
    dst_tail = (cb->data) + (cb->writer);
    src_tail = buf;
    if (nbytes <= (cb->size - cb->writer))
    {
      nbytes_tail = nbytes;
      memmove((void *)dst_tail, (void *)src_tail, nbytes_tail);
      cb->writer += nbytes;
      cb->overflow = 0;
      return nbytes;
    }
    else if (nbytes <= space_cnt)
    {
      nbytes_tail = cb->size - cb->writer;
      int nbytes_head = nbytes - nbytes_tail;
      uint8_t *dst_head, *src_head;
      dst_head = cb->data;
      src_head = (uint8_t *)buf + nbytes_tail;
      memmove((void *)dst_tail, (void *)src_tail, nbytes_tail);
      memmove((void *)dst_head, (void *)src_head, nbytes_head);
      cb->writer = nbytes_head;
      cb->overflow = 0;
      return nbytes;
    }
    else
    {
      nbytes_tail = cb->size - cb->writer;
      int nbytes_head = space_cnt - nbytes_tail;
      uint8_t *dst_head, *src_head;
      dst_head = cb->data;
      src_head = (uint8_t *)buf + nbytes_tail;
      memmove((void *)dst_tail, (void *)src_tail, nbytes_tail);
      memmove((void *)dst_head, (void *)src_head, nbytes_head);
      cb->writer = nbytes_head;
      cb->overflow = nbytes - space_cnt;
      return space_cnt;
    }
  }
  else
  {
    if (nbytes <= space_cnt)
    {
      memmove((void *)(cb->data + cb->writer), buf, nbytes);
      cb->writer += nbytes;
      cb->overflow = 0;
      return nbytes;
    }
    else
    {
      memmove((void *)(cb->data + cb->writer), buf, space_cnt);
      cb->writer += space_cnt;
      cb->overflow = nbytes - space_cnt;
      return space_cnt;
    }
  }
}

uint32_t cb_read(cbuffer_t *cb, void *buf, uint32_t nbytes)
{
  CHECK_NULL(cb, NULL);
  CHECK_NULL(buf, NULL);
  uint32_t data_cnt = cb_data_count(cb);
  CHECK_NULL(data_cnt, 0);
  if ((cb->writer) > (cb->reader))
  {
    if (nbytes < data_cnt)
    {
      memmove(buf, (void *)(cb->data + cb->reader), nbytes);
      cb->reader += nbytes;
      return nbytes;
    }
    else
    {
      memmove(buf, (void *)(cb->data + cb->reader), data_cnt);
      cb->reader += data_cnt;
      return data_cnt;
    }
  }
  else
  {
    int nbytes_tail = 0;
    uint8_t *dst_tail, *src_tail;
    src_tail = (cb->data) + (cb->reader);
    dst_tail = buf;
    if (nbytes < (cb->size - cb->reader))
    {
      nbytes_tail = nbytes;
      memmove((void *)dst_tail, (void *)src_tail, nbytes_tail);
      cb->reader += nbytes;
      return nbytes;
    }
    else if (nbytes <= data_cnt)
    {
      nbytes_tail = cb->size - cb->reader;
      int nbytes_head = nbytes - nbytes_tail;
      uint8_t *dst_head, *src_head;
      src_head = cb->data;
      dst_head = (uint8_t *)buf + nbytes_tail;
      memmove((void *)dst_tail, (void *)src_tail, nbytes_tail);
      memmove((void *)dst_head, (void *)src_head, nbytes_head);
      cb->reader = nbytes_head;
      return nbytes;
    }
    else
    {
      nbytes_tail = cb->size - cb->writer;
      int nbytes_head = data_cnt - nbytes_tail;
      uint8_t *dst_head, *src_head;
      src_head = cb->data;
      dst_head = (uint8_t *)buf + nbytes_tail;
      memmove((void *)dst_tail, (void *)src_tail, nbytes_tail);
      memmove((void *)dst_head, (void *)src_head, nbytes_head);
      cb->reader = nbytes_head;
      return data_cnt;
    }
  }
}
