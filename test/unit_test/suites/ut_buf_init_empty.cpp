//! \file ut_buf_init_empty.cpp
//! \brief Buffer unit test
//! \date  2024-04
//! \author Nicolas Boutin

#include <gtest/gtest.h>

extern "C" {
#include "buffer/buffer.h"
}

using namespace testing;

class BUF_InitEmpty_Fixture : public ::testing::Test {
protected:
  void SetUp() {}

  BUF_t buf;
  static constexpr uint8_t DATA_SIZE = 5;
  std::uint8_t data[DATA_SIZE];
};

TEST_F(BUF_InitEmpty_Fixture, init_empty_001)
{
  BUF_InitEmpty(nullptr, nullptr, 0);
  BUF_InitEmpty(nullptr, nullptr, 1);
  BUF_InitEmpty(nullptr, data, 0);
  BUF_InitEmpty(nullptr, data, 1);
  BUF_InitEmpty(&buf, nullptr, 0);
  BUF_InitEmpty(&buf, nullptr, 1);
  BUF_InitEmpty(&buf, data, 0);
  BUF_InitEmpty(&buf, nullptr, 1);
}

TEST_F(BUF_InitEmpty_Fixture, init_empty_002)
{
  BUF_InitEmpty(&buf, data, DATA_SIZE);

  EXPECT_EQ(buf.size, DATA_SIZE);
  EXPECT_EQ(buf.write_index, 0);
  EXPECT_EQ(buf.read_index, 0);
  EXPECT_EQ(buf.data, data);
}
