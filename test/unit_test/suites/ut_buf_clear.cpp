//! \file ut_buf_clear.cpp
//! \brief Buffer unit test
//! \date  2024-04
//! \author Nicolas Boutin

#include <gtest/gtest.h>

extern "C" {
#include "buffer/buffer.h"
}

using namespace testing;

class BUF_Clear_Fixture : public ::testing::Test
{
protected:
  void SetUp()
  {}
  // attributes
  BUF_t buf;
  static constexpr uint8_t DATA_SIZE = 5;
  std::uint8_t data[DATA_SIZE];
};

TEST_F(BUF_Clear_Fixture, clear_001)
{
  BUF_InitEmpty(&buf, data, DATA_SIZE);
  BUF_WriteUint8(&buf, 0x01);
  BUF_ReadUint8(&buf);

  BUF_Clear(&buf);
  EXPECT_EQ(buf.read_index, 0);
  EXPECT_EQ(buf.write_index, 0);
}
