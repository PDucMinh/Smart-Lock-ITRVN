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
