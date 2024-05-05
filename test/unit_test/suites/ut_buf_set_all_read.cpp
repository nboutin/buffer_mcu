//! \file ut_BUF_set_all_read.cpp
//! \brief Buffer unit test
//! \date  2023-06
//! \author Nicolas Boutin
//! \copyright (C) Copyright Marelli 2023

#include <gtest/gtest.h>

extern "C" {
#include "buffer/buffer.h"
}

using namespace testing;

class BUF_SetAllRead_UT : public ::testing::Test
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
 * \brief Reset read index
 */
TEST_F(BUF_SetAllRead_UT, BUF_SetAllRead_001)
{
  BUF_WriteUint32(&buf, 0x12345678);
  EXPECT_EQ(buf.write_index, 4);

  BUF_SetAllRead(&buf);

  EXPECT_EQ(buf.read_index, 4);
  EXPECT_EQ(buf.write_index, 4);
}
