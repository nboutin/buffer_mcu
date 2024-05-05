//! \file ut_BUF_write_copy.cpp
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
using ::testing::ElementsAreArray;

class BUF_WriteCopy_UT : public ::testing::Test
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

  std::vector<uint8_t> src_data;
  BUF_t src_buf;
};

/**
 * \brief WriteCopy nominal case
 */
TEST_F(BUF_WriteCopy_UT, WriteCopy_001)
{
  src_data = {0x01, 0x02, 0x03, 0x04, 0x05};
  BUF_InitFull(&src_buf, src_data.data(), src_data.size());

  auto copied = BUF_WriteCopy(&buf, &src_buf, src_data.size());

  EXPECT_EQ(copied, src_data.size());
  EXPECT_EQ(buf.write_index, src_data.size());
  EXPECT_EQ(buf.read_index, 0);
  EXPECT_THAT(src_data, ElementsAreArray(buf.data, buf.write_index));
}

/**
 * \brief WriteCopy not enough space in destination buffer
 */
TEST_F(BUF_WriteCopy_UT, WriteCopy_002)
{
  src_data = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C};
  BUF_InitFull(&src_buf, src_data.data(), src_data.size());

  auto copied = BUF_WriteCopy(&buf, &src_buf, src_data.size());

  EXPECT_EQ(copied, DATA_SIZE);
  EXPECT_EQ(buf.write_index, DATA_SIZE);
  EXPECT_EQ(buf.read_index, 0);

  // remove last two element of src_data
  src_data.pop_back();
  src_data.pop_back();
  EXPECT_THAT(src_data, ElementsAreArray(buf.data, buf.write_index));
}

/**
 * \brief WriteCopy requested size to copy is greater than source buffer size
 */
TEST_F(BUF_WriteCopy_UT, WriteCopy_003)
{
  src_data = {0x01, 0x02, 0x03, 0x04, 0x05};
  BUF_InitFull(&src_buf, src_data.data(), src_data.size());

  auto copied = BUF_WriteCopy(&buf, &src_buf, src_data.size() + 1);

  EXPECT_EQ(copied, src_data.size());
  EXPECT_EQ(buf.write_index, src_data.size());
  EXPECT_EQ(buf.read_index, 0);
  EXPECT_THAT(src_data, ElementsAreArray(buf.data, buf.write_index));
}

/**
 * \brief WriteCopy requested size to copy is less than source buffer size
 */
TEST_F(BUF_WriteCopy_UT, WriteCopy_004)
{
  src_data = {0x01, 0x02, 0x03, 0x04, 0x05};
  BUF_InitFull(&src_buf, src_data.data(), src_data.size());

  auto copied = BUF_WriteCopy(&buf, &src_buf, src_data.size() - 1);

  EXPECT_EQ(copied, src_data.size() - 1);
  EXPECT_EQ(buf.write_index, src_data.size() - 1);
  EXPECT_EQ(buf.read_index, 0);

  src_data.pop_back();
  EXPECT_THAT(src_data, ElementsAreArray(buf.data, buf.write_index));
}

/**
 * \brief WriteCopy bad input parameters
 */
TEST_F(BUF_WriteCopy_UT, WriteCopy_005)
{
  src_data = {0x01, 0x02, 0x03, 0x04, 0x05};
  BUF_InitFull(&src_buf, src_data.data(), src_data.size());

  auto copied = BUF_WriteCopy(nullptr, &src_buf, src_data.size());
  EXPECT_EQ(copied, 0);
  EXPECT_EQ(buf.write_index, 0);
  EXPECT_EQ(buf.read_index, 0);

  copied = BUF_WriteCopy(nullptr, nullptr, src_data.size());
  EXPECT_EQ(copied, 0);
  EXPECT_EQ(buf.write_index, 0);
  EXPECT_EQ(buf.read_index, 0);

  copied = BUF_WriteCopy(&buf, nullptr, src_data.size());
  EXPECT_EQ(copied, 0);
  EXPECT_EQ(buf.write_index, 0);
  EXPECT_EQ(buf.read_index, 0);
}
