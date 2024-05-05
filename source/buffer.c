/**
 * \file buffer.c
 * \brief Buffer for MCU
 * \date 2024-04
 * \author Nicolas Boutin
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "buffer/buffer.h"

// --- Private functions

static BUF_size_t buf_Min(BUF_size_t left, BUF_size_t right);
static bool
buf_is_memory_overlapping(const void* dest, const void* src, size_t length);

// --- Public functions

/**
 * \details Does not reset data
 */
void BUF_InitEmpty(BUF_t* buffer, uint8_t* data, BUF_size_t size)
{
  if (buffer != NULL)
  {
    buffer->size        = size;
    buffer->read_index  = 0;
    buffer->write_index = 0;
    if (data != NULL)
    {
      buffer->data = data;
    }
  }
}

void BUF_InitFull(BUF_t* buffer, uint8_t* data, BUF_size_t size)
{
  BUF_InitEmpty(buffer, data, size);
  if (buffer != NULL)
  {
    buffer->write_index = size;
  }
}

void BUF_MakeViewFull(BUF_t* dst_buffer,
                      BUF_t* src_buffer,
                      BUF_size_t start_index,
                      BUF_size_t size)
{
  if ((dst_buffer != NULL) && (src_buffer != NULL)
      && (src_buffer->data != NULL))
  {
    if ((start_index < src_buffer->size) && (size <= src_buffer->size))
    {
      BUF_InitFull(dst_buffer, &src_buffer->data[start_index], size);
    }
    else
    {
      BUF_InitEmpty(dst_buffer, NULL, 0);
    }
  }
}

/**
 * \details Make view from read_index to ToReadCount
 */
void BUF_MakeViewToRead(BUF_t* dst_buffer, BUF_t* src_buffer)
{
  BUF_MakeViewFull(dst_buffer,
                   src_buffer,
                   BUF_GetReadIndex(src_buffer),
                   BUF_GetToReadCount(src_buffer));
}

void BUF_Reset(BUF_t* buffer)
{
  if (buffer != NULL)
  {
    buffer->read_index  = 0;
    buffer->write_index = 0;
  }
}

void BUF_Clear(BUF_t* buffer)
{
  if ((buffer != NULL) && (buffer->data != NULL))
  {
    buffer->read_index  = 0;
    buffer->write_index = 0;
    memset(buffer->data, 0x00, buffer->size);
  }
}

void BUF_SetSize(BUF_t* buffer, BUF_size_t new_size)
{
  if ((buffer != NULL) && (BUF_GetSize(buffer) > new_size))
  {
    buffer->size = new_size; // Update size

    // Update read_index and write_index if needed
    if (buffer->write_index > new_size)
    {
      buffer->write_index = new_size;
    }
    if (buffer->read_index > new_size)
    {
      buffer->read_index = new_size;
    }
  }
}

BUF_size_t BUF_GetSize(const BUF_t* buffer)
{
  BUF_size_t size = 0;
  if (buffer != NULL)
  {
    size = buffer->size;
  }
  return size;
}

bool BUF_IsEmpty(const BUF_t* buffer)
{
  bool is_empty = true;
  if (buffer != NULL)
  {
    if (buffer->write_index > 0)
    {
      is_empty = false;
    }
  }
  return is_empty;
}

bool BUF_IsFull(const BUF_t* buffer)
{
  bool is_full = false;
  if (buffer != NULL)
  {
    if (buffer->write_index == buffer->size)
    {
      is_full = true;
    }
  }
  return is_full;
}

BUF_size_t BUF_GetFreeSize(const BUF_t* buffer)
{
  BUF_size_t free_size = 0;
  if (buffer != NULL)
  {
    free_size = buffer->size - buffer->write_index;
  }
  return free_size;
}

BUF_size_t BUF_GetUsedSize(const BUF_t* buffer)
{
  BUF_size_t used_size = 0;
  if (buffer != NULL)
  {
    used_size = buffer->write_index;
  }
  return used_size;
}

BUF_size_t BUF_GetToReadCount(const BUF_t* buffer)
{
  BUF_size_t to_read_count = 0;
  if (buffer != NULL)
  {
    to_read_count = buffer->write_index - buffer->read_index;
  }
  return to_read_count;
}

// Add protection to not read after write_index ??
BUF_size_t BUF_GetReadIndex(const BUF_t* buffer)
{
  BUF_size_t read_index = 0;
  if (buffer != NULL)
  {
    read_index = buffer->read_index;
  }
  return read_index;
}

void BUF_ResetReadIndex(BUF_t* buffer)
{
  if (buffer != NULL)
  {
    buffer->read_index = 0;
  }
}

void BUF_SetAllRead(BUF_t* buffer)
{
  if (buffer != NULL)
  {
    buffer->read_index = buffer->write_index;
  }
}

uint8_t BUF_GetUint8(const BUF_t* buffer, BUF_size_t index)
{
  uint8_t value = 0;
  if ((buffer != NULL) && (buffer->data != NULL) && (index < buffer->size))
  {
    value = buffer->data[index];
  }
  return value;
}

uint16_t BUF_GetUint16(const BUF_t* buffer, BUF_size_t index)
{
  uint16_t value = 0;
  if ((buffer != NULL) && (buffer->data != NULL)
      && ((index + 1) < buffer->size))
  {
    value = (uint16_t) ((uint16_t) (buffer->data[index] << 8U)
                        | buffer->data[index + 1]);
  }
  return value;
}

uint32_t BUF_GetUint32(const BUF_t* buffer, BUF_size_t index)
{
  uint32_t value = 0;
  if ((buffer != NULL) && (buffer->data != NULL)
      && ((index + 3) < buffer->size))
  {
    value = (uint32_t) ((uint32_t) (buffer->data[index] << 24U)
                        | (uint32_t) (buffer->data[index + 1] << 16U)
                        | (uint32_t) (buffer->data[index + 2] << 8U)
                        | buffer->data[index + 3]);
  }
  return value;
}

uint8_t BUF_GetLastUint8(const BUF_t* buffer)
{
  uint8_t value = 0;
  if ((buffer != NULL) && (buffer->data != NULL) && (buffer->write_index > 0))
  {
    value = buffer->data[buffer->write_index - 1];
  }
  return value;
}

uint8_t BUF_PutUint8(BUF_t* buffer, uint8_t data, BUF_size_t index)
{
  uint8_t written = 0;
  if ((buffer != NULL) && (buffer->data != NULL) && (index < buffer->size))
  {
    buffer->data[index] = data;
    written             = 1;
  }
  return written;
}

uint8_t BUF_PutUint16(BUF_t* buffer, uint16_t data, BUF_size_t index)
{
  uint8_t written = 0;
  if ((buffer != NULL) && (buffer->data != NULL)
      && ((index + 1) < buffer->size))
  {
    buffer->data[index]     = (uint8_t) ((data & 0xFF00U) >> 8U);
    buffer->data[index + 1] = (uint8_t) (data & 0xFFU);
    written                 = 2;
  }
  return written;
}

uint8_t BUF_PutUint32(BUF_t* buffer, uint32_t data, BUF_size_t index)
{
  uint8_t written = 0;
  if ((buffer != NULL) && (buffer->data != NULL)
      && ((index + 3) < buffer->size))
  {
    buffer->data[index]     = (uint8_t) ((data & 0xFF000000U) >> 24U);
    buffer->data[index + 1] = (uint8_t) ((data & 0xFF0000U) >> 16U);
    buffer->data[index + 2] = (uint8_t) ((data & 0xFF00U) >> 8U);
    buffer->data[index + 3] = (uint8_t) (data & 0xFFU);
    written                 = 4;
  }
  return written;
}

uint8_t BUF_ReadUint8(BUF_t* buffer)
{
  uint8_t read = 0;
  if ((buffer != NULL) && (buffer->data != NULL)
      && (BUF_GetToReadCount(buffer) >= 1))
  {
    read = buffer->data[buffer->read_index];
    buffer->read_index += 1;
  }
  return read;
}

uint16_t BUF_ReadUint16(BUF_t* buffer)
{
  uint16_t read = 0;
  if ((buffer != NULL) && (BUF_GetToReadCount(buffer) >= 2))
  {
    read = (uint16_t) (BUF_ReadUint8(buffer) << 8U);
    read |= BUF_ReadUint8(buffer);
  }
  return read;
}

uint32_t BUF_ReadUint32(BUF_t* buffer)
{
  uint32_t read = 0;
  if ((buffer != NULL) && (BUF_GetToReadCount(buffer) >= 4))
  {
    read = (uint32_t) BUF_ReadUint8(buffer) << 24U;
    read |= (uint32_t) BUF_ReadUint8(buffer) << 16U;
    read |= (uint32_t) BUF_ReadUint8(buffer) << 8U;
    read |= (uint32_t) BUF_ReadUint8(buffer);
  }
  return read;
}

uint8_t BUF_WriteUint8(BUF_t* buffer, uint8_t data)
{
  uint8_t written = 0;
  if ((buffer != NULL) && (buffer->data != NULL)
      && (BUF_GetFreeSize(buffer) > 0))
  {
    buffer->data[buffer->write_index] = data;
    buffer->write_index++;
    written = 1;
  }
  return written;
}

uint8_t BUF_WriteUint16(BUF_t* buffer, uint16_t data)
{
  uint8_t written = 0;
  written += BUF_WriteUint8(buffer, (uint8_t) (data >> 8U));
  written += BUF_WriteUint8(buffer, (uint8_t) (data));
  return written;
}

uint8_t BUF_WriteUint32(BUF_t* buffer, uint32_t data)
{
  uint8_t written = 0;
  written += BUF_WriteUint8(buffer, (uint8_t) (data >> 24U));
  written += BUF_WriteUint8(buffer, (uint8_t) (data >> 16U));
  written += BUF_WriteUint8(buffer, (uint8_t) (data >> 8U));
  written += BUF_WriteUint8(buffer, (uint8_t) (data));
  return written;
}

uint8_t BUF_WriteUint64(BUF_t* buffer, uint64_t data)
{
  uint8_t written = 0;
  written += BUF_WriteUint8(buffer, (uint8_t) (data >> 56U));
  written += BUF_WriteUint8(buffer, (uint8_t) (data >> 48U));
  written += BUF_WriteUint8(buffer, (uint8_t) (data >> 40U));
  written += BUF_WriteUint8(buffer, (uint8_t) (data >> 32U));
  written += BUF_WriteUint8(buffer, (uint8_t) (data >> 24U));
  written += BUF_WriteUint8(buffer, (uint8_t) (data >> 16U));
  written += BUF_WriteUint8(buffer, (uint8_t) (data >> 8U));
  written += BUF_WriteUint8(buffer, (uint8_t) (data));
  return written;
}

BUF_size_t BUF_WriteString(BUF_t* buffer, const char* string, BUF_size_t size)
{
  return BUF_WriteRaw(buffer, (const uint8_t*) string, size);
}

BUF_size_t BUF_WriteRaw(BUF_t* buffer, const uint8_t* data, BUF_size_t size)
{
  BUF_size_t written = 0;
  if ((buffer != NULL) && (data != NULL) && (size > 0)
      && (BUF_GetFreeSize(buffer) >= size)
      && (buf_is_memory_overlapping(buffer->data, data, size) == false))
  {
    memcpy(&buffer->data[buffer->write_index], data, size);
    buffer->write_index += size;
    written = size;
  }
  return written;
}

/**
 * \details Copy data from source.read_index to destination.write_index
 */
BUF_size_t BUF_WriteCopy(BUF_t* dst, BUF_t* src, BUF_size_t size)
{
  BUF_size_t dst_free_size     = BUF_GetFreeSize(dst);
  BUF_size_t src_to_read_count = BUF_GetToReadCount(src);
  BUF_size_t to_copy           = buf_Min(dst_free_size, src_to_read_count);
  to_copy                      = buf_Min(to_copy, size);

  if ((dst != NULL) && (dst->data != NULL) && (src != NULL)
      && (src->data != NULL)
      && (buf_is_memory_overlapping(dst->data, src->data, to_copy) == false))
  {
    memcpy(&dst->data[dst->write_index], &src->data[src->read_index], to_copy);
    dst->write_index += to_copy;
    src->read_index += to_copy;
  }
  else
  {
    to_copy = 0;
  }
  return to_copy;
}

BUF_size_t BUF_FillPattern(BUF_t* buffer, uint8_t pattern, BUF_size_t size)
{
  BUF_size_t free_size = BUF_GetFreeSize(buffer);
  BUF_size_t to_fill   = buf_Min(free_size, size);

  if ((buffer != NULL) && (buffer->data != NULL) && (size > 0))
  {
    memset(&buffer->data[buffer->write_index], (int) pattern, to_fill);
    buffer->write_index += to_fill;
  }
  else
  {
    to_fill = 0;
  }
  return to_fill;
}

const uint8_t* BUF_GetData(const BUF_t* buffer)
{
  const uint8_t* data = NULL;
  if (buffer != NULL)
  {
    data = buffer->data;
  }
  return data;
}

uint8_t* BUF_GetDataNoConst(const BUF_t* buffer)
{
  uint8_t* data = NULL;
  if (buffer != NULL)
  {
    data = buffer->data;
  }
  return data;
}

bool BUF_Compare(const BUF_t* buf, const uint8_t* data, BUF_size_t size)
{
  bool equal = false;

  if ((buf != NULL) && (buf->data != NULL) && (data != NULL)
      && (BUF_GetSize(buf) >= size))
  {
    equal = (memcmp(buf->data, data, size) == 0);
  }
  return equal;
}

// --- Private functions

/**
 * \brief Get minimum value
 * \param left Left value
 * \param right Right value
 * \return Minimum value
 */
static BUF_size_t buf_Min(BUF_size_t left, BUF_size_t right)
{
  return (left <= right) ? left : right;
}

static bool
buf_is_memory_overlapping(const void* dest, const void* src, size_t length)
{
  bool is_overlapping = false;

  if ((dest != NULL) && (src != NULL))
  {
    uintptr_t dest_start = (uintptr_t) dest;
    uintptr_t dest_end   = dest_start + length;
    uintptr_t src_start  = (uintptr_t) src;
    uintptr_t src_end    = src_start + length;

    is_overlapping = ((dest_start >= src_start) && (dest_start < src_end))
                     || ((src_start >= dest_start) && (src_start < dest_end));
  }
  return is_overlapping;
}
