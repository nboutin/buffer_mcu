//! \file ut_buf_is_full.cpp
//! \brief Buffer unit test
//! \date  2024-04
//! \author Nicolas Boutin

#include <gtest/gtest.h>

extern "C" {
#include "buffer/buffer.h"
}

using namespace testing;

class BUF_IsFull_Fixture : public ::testing::Test
{
protected:
  void SetUp()
  {}
  // attributes
  BUF_t buf;
  static constexpr uint8_t DATA_SIZE = 5;
  std::uint8_t data[DATA_SIZE];
};

TEST_F(BUF_IsFull_Fixture, is_full_001)
{
  BUF_InitFull(&buf, data, DATA_SIZE);
  bool is_full = BUF_IsFull(&buf);
  EXPECT_TRUE(is_full);
}

TEST_F(BUF_IsFull_Fixture, is_full_002)
{
  BUF_InitEmpty(&buf, data, DATA_SIZE);
  BUF_WriteUint8(&buf, 0x01);
  BUF_WriteUint8(&buf, 0x02);
  BUF_WriteUint8(&buf, 0x03);
  BUF_WriteUint8(&buf, 0x04);
  BUF_WriteUint8(&buf, 0x05);

  bool is_full = BUF_IsFull(&buf);
  EXPECT_TRUE(is_full);
}
