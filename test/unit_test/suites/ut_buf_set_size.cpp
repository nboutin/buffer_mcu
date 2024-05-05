//! \file ut_buf_set_size.cpp
//! \brief Buffer unit test
//! \date  2024-04
//! \author Nicolas Boutin

#include <gtest/gtest.h>

extern "C" {
#include "buffer/buffer.h"
}

using namespace testing;

class BUF_SetSize_Fixture : public ::testing::Test
{
protected:
  void SetUp()
  {
    BUF_InitEmpty(&buf, data, DATA_SIZE);
  }

  // attributes
  BUF_t buf;
  static constexpr uint8_t DATA_SIZE = 10;
  std::uint8_t data[DATA_SIZE];
};

/**
 * \brief Update BUF size with SetSize
 */
TEST_F(BUF_SetSize_Fixture, BUF_SetSize_001)
{
  BUF_SetSize(&buf, DATA_SIZE - 2);
  EXPECT_EQ(buf.size, DATA_SIZE - 2);
}

/**
 * \brief SetSize with size > buffer size
 */
TEST_F(BUF_SetSize_Fixture, BUF_SetSize_002)
{
  BUF_SetSize(&buf, DATA_SIZE + 5);
  EXPECT_EQ(buf.size, DATA_SIZE);
}

/**
 * \brief write_index position > new size
 */
TEST_F(BUF_SetSize_Fixture, BUF_SetSize_003)
{
  BUF_WriteUint32(&buf, 0x12345678);
  BUF_SetSize(&buf, 3);
  EXPECT_EQ(buf.write_index, 3);
  EXPECT_EQ(buf.size, 3);
}

/**
 * \brief read_index position > new size
 */
TEST_F(BUF_SetSize_Fixture, BUF_SetSize_004)
{
  BUF_WriteUint32(&buf, 0x12345678);
  BUF_ReadUint32(&buf);
  BUF_SetSize(&buf, 3);
  EXPECT_EQ(buf.read_index, 3);
  EXPECT_EQ(buf.size, 3);
}
