#include "cbuffer.h"

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
  if ((cb != NULL) && (buf != NULL) && (cb->overflow == FALSE))
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
