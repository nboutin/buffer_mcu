//! \file ut_BUF_fill_pattern.cpp
//! \brief Buffer unit test
//! \date  2023-06
//! \author Nicolas Boutin
//! \copyright (C) Copyright Marelli 2026

#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include "buffer/buffer.h"
}

using namespace testing;
using ::testing::Each;

class BUF_FillPattern_UT : public ::testing::Test
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
 * \brief FillPattern nominal case
 */
TEST_F(BUF_FillPattern_UT, FillPattern_001)
{
  auto res = BUF_FillPattern(&buf, 0x55, DATA_SIZE);

  EXPECT_EQ(res, DATA_SIZE);
  EXPECT_EQ(buf.write_index, DATA_SIZE);

  std::vector<uint8_t> BUF_data = {buf.data, buf.data + DATA_SIZE};
  EXPECT_THAT(BUF_data, Each(Eq(0x55)));
}

/**
 * \brief FillPattern not from index zero and not to the end
 */
TEST_F(BUF_FillPattern_UT, FillPattern_002)
{
  BUF_WriteUint16(&buf, 0x1122);
  auto res = BUF_FillPattern(&buf, 0x55, 6);

  EXPECT_EQ(res, 6);
  EXPECT_EQ(buf.write_index, 8);
  std::vector<uint8_t> expected = {0x11, 0x22, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55};
  EXPECT_THAT(expected, ElementsAreArray(buf.data, buf.write_index));
}

/**
 * \brief FillPattern bad input parameters
 */
TEST_F(BUF_FillPattern_UT, FillPattern_003)
{
  auto res = BUF_FillPattern(&buf, 0x55, 0);
  EXPECT_EQ(res, 0);
  EXPECT_EQ(buf.write_index, 0);

  res = BUF_FillPattern(nullptr, 0x55, 4);
  EXPECT_EQ(res, 0);
  EXPECT_EQ(buf.write_index, 0);

  res = BUF_FillPattern(nullptr, 0x55, 0);
  EXPECT_EQ(res, 0);
  EXPECT_EQ(buf.write_index, 0);
}
