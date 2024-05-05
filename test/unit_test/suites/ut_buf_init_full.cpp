//! \file ut_BUF_init_full.cpp
//! \brief Buffer unit test
//! \date  2022/09
//! \author Nicolas Boutin
//! \copyright (C) Copyright Marelli 2022

#include <gtest/gtest.h>

extern "C" {
#include "buffer/buffer.h"
}

using namespace testing;

class BUF_InitFull_Fixture : public ::testing::Test
{
protected:
  void SetUp()
  {}
  // attributes
  BUF_t buf;
  static constexpr uint8_t DATA_SIZE = 5;
  std::uint8_t data[DATA_SIZE];
};

TEST_F(BUF_InitFull_Fixture, init_full_001)
{
  BUF_InitFull(nullptr, nullptr, 0);
  BUF_InitFull(nullptr, nullptr, 1);
  BUF_InitFull(nullptr, data, 0);
  BUF_InitFull(nullptr, data, 1);
  BUF_InitFull(&buf, nullptr, 0);
  BUF_InitFull(&buf, nullptr, 1);
  BUF_InitFull(&buf, data, 0);
  BUF_InitFull(&buf, nullptr, 1);
}

TEST_F(BUF_InitFull_Fixture, init_full_002)
{
  BUF_InitFull(&buf, data, DATA_SIZE);

  EXPECT_EQ(buf.size, DATA_SIZE);
  EXPECT_EQ(buf.write_index, DATA_SIZE);
  EXPECT_EQ(buf.read_index, 0);
  EXPECT_EQ(buf.data, data);
}
