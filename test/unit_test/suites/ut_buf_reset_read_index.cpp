//! \file ut_BUF_reset_read_index.cpp
//! \brief Buffer unit test
//! \date  2023-06
//! \author Nicolas Boutin
//! \copyright (C) Copyright Marelli 2023

#include <gtest/gtest.h>

extern "C" {
#include "buffer/buffer.h"
}

using namespace testing;

class BUF_ResetReadIndex_UT : public ::testing::Test
{
protected:
  void SetUp()
  {
    BUF_InitFull(&buf, data, DATA_SIZE);
  }

  // attributes
  BUF_t buf;
  static constexpr uint8_t DATA_SIZE = 10;
  std::uint8_t data[DATA_SIZE];
};

/**
 * \brief Reset read index
 */
TEST_F(BUF_ResetReadIndex_UT, BUF_ResetReadIndex_001)
{
  BUF_WriteUint32(&buf, 0x12345678);
  BUF_ReadUint32(&buf);

  BUF_ResetReadIndex(&buf);
  EXPECT_EQ(buf.read_index, 0);
}
