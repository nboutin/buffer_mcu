//! \file ut_buf_compare.cpp
//! \brief Buffer unit test
//! \date  2024-04
//! \author Nicolas Boutin

#include <gtest/gtest.h>

extern "C" {
#include "buffer/buffer.h"
}

using namespace testing;

class BUF_Compare_UT : public ::testing::Test
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
 * \brief BUF_Compare_UT nominal case equal
 */
TEST_F(BUF_Compare_UT, Compare_001)
{
  std::vector<std::uint8_t> in_data = {0xAA, 0xBB, 0xCC, 0xDD};
  BUF_WriteRaw(&buf, in_data.data(), in_data.size());

  auto res = BUF_Compare(&buf, in_data.data(), in_data.size());
  EXPECT_TRUE(res);
}

/**
 * \brief BUF_Compare_UT nominal case not equal
 */
TEST_F(BUF_Compare_UT, Compare_002)
{
  BUF_WriteUint8(&buf, 0x11);
  std::vector<std::uint8_t> in_data = {0xAA, 0xBB, 0xCC, 0xDD};
  BUF_WriteRaw(&buf, in_data.data(), in_data.size());

  auto res = BUF_Compare(&buf, in_data.data(), in_data.size());
  EXPECT_FALSE(res);
}

