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
  // if (buf == NULL || nbytes == 0)
  // {
  //   return 0;
  // }
  // if (cb == NULL || cb->active == false)
  // {
  //   cb_init(cb, buf, nbytes);
  //   return nbytes;
  // }
}
uint32_t cb_read(cbuffer_t *cb, void *buf, uint32_t nbytes)
{
}
