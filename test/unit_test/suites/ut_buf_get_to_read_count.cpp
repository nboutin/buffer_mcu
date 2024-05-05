//! \file ut_buf_get_to_read_count.cpp
//! \brief Buffer unit test
//! \date  2024-04
//! \author Nicolas Boutin

#include <gtest/gtest.h>

extern "C" {
#include "buffer/buffer.h"
}

using namespace testing;

class BUF_GetToReadCount_Fixture : public ::testing::Test
{
protected:
  void SetUp()
  {}
  // attributes
  BUF_t buf;
  static constexpr uint8_t DATA_SIZE = 5;
  std::uint8_t data[DATA_SIZE];
};

/**
 * \brief Get to read count on empty buffer
 */
TEST_F(BUF_GetToReadCount_Fixture, get_to_read_count_001)
{
  BUF_InitEmpty(&buf, data, DATA_SIZE);
  BUF_size_t to_read_count = BUF_GetToReadCount(&buf);
  EXPECT_EQ(to_read_count, 0);
}

/**
 * \brief Get to read count on full buffer
 */
TEST_F(BUF_GetToReadCount_Fixture, get_to_read_count_002)
{
  BUF_InitFull(&buf, data, DATA_SIZE);
  BUF_size_t to_read_count = BUF_GetToReadCount(&buf);
  EXPECT_EQ(to_read_count, DATA_SIZE);
}

/**
 * \brief Get to read count on buffer with one byte written
 */
TEST_F(BUF_GetToReadCount_Fixture, get_to_read_count_003)
{
  BUF_InitEmpty(&buf, data, DATA_SIZE);
  BUF_WriteUint8(&buf, 0x01);
  BUF_size_t to_read_count = BUF_GetToReadCount(&buf);
  EXPECT_EQ(to_read_count, 1);
}

/**
 * \brief Get to read count on buffer with one byte written and one byte read
 */
TEST_F(BUF_GetToReadCount_Fixture, get_to_read_count_004)
{
  BUF_InitEmpty(&buf, data, DATA_SIZE);
  BUF_WriteUint8(&buf, 0x01);
  BUF_ReadUint8(&buf);
  BUF_size_t to_read_count = BUF_GetToReadCount(&buf);
  EXPECT_EQ(to_read_count, 0);
}
