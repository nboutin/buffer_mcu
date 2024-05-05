//! \file ut_BUF_get_size.cpp
//! \brief Buffer unit test
//! \date  2022/09
//! \author Nicolas Boutin
//! \copyright (C) Copyright Marelli 2022

#include <gtest/gtest.h>

extern "C" {
#include "buffer/buffer.h"
}

using namespace testing;

class BUF_GetSize_Fixture : public ::testing::Test
{
protected:
  void SetUp()
  {}
  // attributes
  BUF_t buf;
  static constexpr uint8_t DATA_SIZE = 5;
  std::uint8_t data[DATA_SIZE];
};

TEST_F(BUF_GetSize_Fixture, get_size_001)
{
  BUF_InitFull(&buf, data, DATA_SIZE);
  BUF_size_t size = BUF_GetSize(&buf);
  EXPECT_EQ(size, DATA_SIZE);
}
