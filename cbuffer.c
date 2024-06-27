#include "cbuffer.h"

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
