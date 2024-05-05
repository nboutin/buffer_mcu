//! \file ut_BUF_reset.cpp
//! \brief Buffer unit test
//! \date  2022/09
//! \author Nicolas Boutin
//! \copyright (C) Copyright Marelli 2022

#include <gtest/gtest.h>

extern "C" {
#include "buffer/buffer.h"
}

using namespace testing;

class BUF_Reset_Fixture : public ::testing::Test
{
protected:
  void SetUp()
  {
    BUF_InitFull(&buf, data, DATA_SIZE);
  }
  // attributes
  BUF_t buf;
  static constexpr uint8_t DATA_SIZE = 5;
  std::uint8_t data[DATA_SIZE];
};

TEST_F(BUF_Reset_Fixture, reset_001)
{
  BUF_ReadUint8(&buf);

  BUF_Reset(&buf);
  EXPECT_EQ(buf.read_index, 0);
  EXPECT_EQ(buf.write_index, 0);
}
