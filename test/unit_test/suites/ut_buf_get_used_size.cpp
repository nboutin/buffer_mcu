//! \file ut_buf_get_used_size.cpp
//! \brief Buffer unit test
//! \date  2024-04
//! \author Nicolas Boutin

#include <gtest/gtest.h>

extern "C" {
#include "buffer/buffer.h"
}

using namespace testing;

class BUF_GetUsedSize_Fixture : public ::testing::Test
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
 * \brief Get used size on empty buffer
 */
TEST_F(BUF_GetUsedSize_Fixture, get_used_size_001)
{
  BUF_InitEmpty(&buf, data, DATA_SIZE);
  BUF_size_t used_size = BUF_GetUsedSize(&buf);
  EXPECT_EQ(used_size, 0);
}

/**
 * \brief Get used size on full buffer
 */
TEST_F(BUF_GetUsedSize_Fixture, get_used_size_002)
{
  BUF_InitFull(&buf, data, DATA_SIZE);
  BUF_size_t used_size = BUF_GetUsedSize(&buf);
  EXPECT_EQ(used_size, DATA_SIZE);
}

/**
 * \brief Get used size on buffer with one byte written
 */
TEST_F(BUF_GetUsedSize_Fixture, get_used_size_003)
{
  BUF_InitEmpty(&buf, data, DATA_SIZE);
  BUF_WriteUint8(&buf, 0x01);
  BUF_size_t used_size = BUF_GetUsedSize(&buf);
  EXPECT_EQ(used_size, 1);
}

/**
 * \brief Get used size on buffer with one byte written and one byte read
 */
TEST_F(BUF_GetUsedSize_Fixture, get_used_size_004)
{
  BUF_InitEmpty(&buf, data, DATA_SIZE);
  BUF_WriteUint8(&buf, 0x01);
  BUF_ReadUint8(&buf);
  BUF_size_t used_size = BUF_GetUsedSize(&buf);
  EXPECT_EQ(used_size, 1);
}
