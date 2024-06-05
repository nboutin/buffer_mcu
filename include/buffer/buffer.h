/**
 * \file buffer.h
 * \brief Buffer for MCU
 * \date 2024-04
 * \author Nicolas Boutin
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

// --- Public type

/**
 * \brief Buffer size type
 */
typedef uint16_t BUF_size_t;

/**
 * \brief Buffer structure
 * \warning Do not use this structure directly, use BUF API instead
 */
typedef struct {
  uint8_t* data;          /*!< Buffer data */
  BUF_size_t write_index; /*!< Write index */
  BUF_size_t read_index;  /*!< Read index */
  BUF_size_t size;        /*!< Buffer size */
} BUF_t;

// --- Public function

/**
 * \brief Buffer initialization
 * \param buffer Buffer to initialize
 * \param data Buffer data
 * \param size Buffer size
 */
void BUF_InitEmpty(BUF_t* buffer, uint8_t* data, BUF_size_t size);

/**
 * \brief Buffer initialization
 * \param buffer Buffer to initialize
 * \param data Buffer data
 * \param size Buffer size
 */
void BUF_InitFull(BUF_t* buffer, uint8_t* data, BUF_size_t size);

/**
 * \brief Make buffer view on existing buffer
 * \details Update read_index, write_index and data starting pointer
 * \warning dst_buffer and src_buffer are sharing the same data
 * \param dst_buffer Destination buffer
 * \param src_buffer Source buffer
 * \param start_index Start index
 * \param size Size to make view on
 */
void BUF_MakeViewFull(BUF_t* dst_buffer,
                      BUF_t* src_buffer,
                      BUF_size_t start_index,
                      BUF_size_t size);

/**
 * \brief Make buffer view on existing buffer with only data left to read
 * \details Update read_index, write_index and data starting pointer
 * \warning dst_buffer and src_buffer are sharing the same data
 * \param dst_buffer Destination buffer
 * \param src_buffer Source buffer
 */
void BUF_MakeViewToRead(BUF_t* dst_buffer, BUF_t* src_buffer);

/**
 * \brief Reset buffer read index and write index
 * \param buffer Buffer to reset
 * \details Does not erase data
 */
void BUF_Reset(BUF_t* buffer);

/**
 * \brief Clear buffer
 * \param buffer Buffer to clear
 * \details Erase data and reset read index and write index
 */
void BUF_Clear(BUF_t* buffer);

/**
 * \brief Get buffer size
 * \param buffer Buffer to get
 * \return Buffer size
 */
BUF_size_t BUF_GetSize(const BUF_t* buffer);

/**
 * \brief Set buffer size
 * \param buffer Buffer to set
 * \param new_size New buffer size
 */
void BUF_SetSize(BUF_t* buffer, BUF_size_t new_size);

/**
 * \brief Is buffer empty
 * \details write_index == 0, no written nor read
 * \param buffer Buffer to check
 * \return TRUE if empty, FALSE otherwise
 */
bool BUF_IsEmpty(const BUF_t* buffer);

/**
 * \brief Is buffer full
 * \param buffer Buffer to check
 * \return TRUE if full, FALSE otherwise
 * \details write_index == size
 */
bool BUF_IsFull(const BUF_t* buffer);

/**
 * \brief Get free space in buffer
 * \param buffer Buffer to check
 * \return Free space in buffer
 * \details size - write_index
 */
BUF_size_t BUF_GetFreeSize(const BUF_t* buffer);

/**
 * \brief Get used space in buffer
 * \param buffer Buffer to check
 * \return Used space in buffer
 * \details write_index
 */
BUF_size_t BUF_GetUsedSize(const BUF_t* buffer);

/**
 * \brief Get data to read in buffer
 * \param buffer Buffer to check
 * \return Data to read count in buffer
 * \details write_index - read_index
 */
BUF_size_t BUF_GetToReadCount(const BUF_t* buffer);

/**
 * \brief Get read index
 * \param buffer Buffer to check
 * \return read_index
 */
BUF_size_t BUF_GetReadIndex(const BUF_t* buffer);

/**
 * \brief Reset read index
 * \param buffer to reset
 */
void BUF_ResetReadIndex(BUF_t* buffer);

/**
 * \brief Set buffer as all read
 * \param buffer Buffer to set
 */
void BUF_SetAllRead(BUF_t* buffer);

/**
 * \brief Get data by index without modify read_index and write_index
 * \param buffer Buffer to get from
 * \param index Index to get
 * \return Data at index
 * \see BUF_ReadUint8 \see BUF_WriteUint8
 */
uint8_t BUF_GetUint8(const BUF_t* buffer, BUF_size_t index);

/**
 * \brief Get data by index without modify read_index and write_index
 * \param buffer Buffer to get from
 * \param index Index to get
 * \return Data at index
 * \see BUF_ReadUint16 \see BUF_WriteUint16
 */
uint16_t BUF_GetUint16(const BUF_t* buffer, BUF_size_t index);

/**
 * \brief Get data by index without modify read_index and write_index
 * \param buffer Buffer to get from
 * \param index Index to get
 * \return Data at index
 * \see BUF_ReadUint32 \see BUF_WriteUint32
 */
uint32_t BUF_GetUint32(const BUF_t* buffer, BUF_size_t index);

/**
 * \brief Get last data without modify read_index and write_index
 * \param buffer Buffer to check
 * \return Last data
 */
uint8_t BUF_GetLastUint8(const BUF_t* buffer);

/**
 * \brief Put 1 byte in buffer at index
 * \param buffer Buffer to put in
 * \param data Data to put
 * \param index Index to put at
 * \return number of byte written
 */
uint8_t BUF_PutUint8(BUF_t* buffer, uint8_t data, BUF_size_t index);

/**
 * \brief Put 2 bytes in buffer at index
 * \param buffer Buffer to put in
 * \param data Data to put
 * \param index Index to put at
 * \return number of byte written
 */
uint8_t BUF_PutUint16(BUF_t* buffer, uint16_t data, BUF_size_t index);

/**
 * \brief Put 4 bytes in buffer at index
 * \param buffer Buffer to put in
 * \param data Data to put
 * \param index Index to put at
 * \return number of byte written
 */
uint8_t BUF_PutUint32(BUF_t* buffer, uint32_t data, BUF_size_t index);

/**
 * \brief Read 1 byte from buffer
 * \param buffer Buffer to read
 * \return data read
 */
uint8_t BUF_ReadUint8(BUF_t* buffer);

/**
 * \brief Read 2 bytes from buffer
 * \param buffer Buffer to read
 * \return data read
 */
uint16_t BUF_ReadUint16(BUF_t* buffer);

/**
 * \brief Read 4 bytes from buffer
 * \param buffer Buffer to read
 * \return data read
 */
uint32_t BUF_ReadUint32(BUF_t* buffer);

/**
 * \brief Write 1 byte to buffer
 * \param buffer Buffer to write to
 * \param data Data to write
 * \return written byte count, 0 if error
 */
uint8_t BUF_WriteUint8(BUF_t* buffer, uint8_t data);

/**
 * \brief Write 2 bytes to buffer
 * \param buffer Buffer to write to
 * \param data Data to write
 * \return written byte count, 0 if error
 */
uint8_t BUF_WriteUint16(BUF_t* buffer, uint16_t data);

/**
 * \brief Write 4 bytes to buffer
 * \param buffer Buffer to write to
 * \param data Data to write
 * \return written byte count, 0 if error
 */
uint8_t BUF_WriteUint32(BUF_t* buffer, uint32_t data);

/**
 * \brief Write 8 bytes to buffer
 * \param buffer Buffer to write to
 * \param data Data to write
 * \return written byte count, 0 if error
 */
uint8_t BUF_WriteUint64(BUF_t* buffer, uint64_t data);

/**
 * \brief Write string to buffer
 * \param buffer Buffer to write to
 * \param string String to write
 * \param size String size
 * \return written byte count, 0 if error
 */
BUF_size_t BUF_WriteString(BUF_t* buffer, const char* string, BUF_size_t size);

/**
 * \brief Write raw data to buffer
 * \param buffer Buffer to write to
 * \param data Data to write
 * \param size Data size
 * \return written byte count, 0 if error
 */
BUF_size_t BUF_WriteRaw(BUF_t* buffer, const uint8_t* data, BUF_size_t size);

/**
 * \brief Copy from src buffer read index to dst buffer write index
 * \param dst Destination buffer
 * \param src Source buffer
 * \param size Size to copy
 * \return Size copied
 */
BUF_size_t BUF_WriteCopy(BUF_t* dst, BUF_t* src, BUF_size_t size);

/**
 * \brief Fill buffer with pattern
 * \param buffer Buffer to fill
 * \param pattern Pattern to fill
 * \param size Size to fill
 * \return Size filled
 */
BUF_size_t BUF_FillPattern(BUF_t* buffer, uint8_t pattern, BUF_size_t size);

/**
 * \brief Get buffer private data
 * \param buffer Buffer to get data on
 * \return Data private
 */
const uint8_t* BUF_GetData(const BUF_t* buffer);

/**
 * \brief Get buffer private data
 * \param buffer Buffer to get data on
 * \return Data private
 * \warning To be used only for older api that does not require const
 */
uint8_t* BUF_GetDataNoConst(const BUF_t* buffer);

/**
 * \brief Compare buffer with data
 * \param buffer Buffer to compare
 * \param data Data to compare
 * \param size Data size to compare
 * \return true if equal, false otherwise
 */
bool BUF_Compare(const BUF_t* buffer1, const uint8_t* data, BUF_size_t size);
