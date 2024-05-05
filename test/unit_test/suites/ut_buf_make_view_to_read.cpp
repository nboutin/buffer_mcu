//! \file ut_BUF_make_view_to_read.cpp
//! \brief Buffer unit test
//! \date  2022/09
//! \author Nicolas Boutin
//! \copyright (C) Copyright Marelli 2022

#include <gtest/gtest.h>

extern "C" {
#include "buffer/buffer.h"
}

using namespace testing;

class BUF_MakeViewToRead_Fixture : public ::testing::Test
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

/**
 * \brief Make buffer view, no data read
 */
TEST_F(BUF_MakeViewToRead_Fixture, make_view_to_read_001)
{
  BUF_t BUF_view;
  BUF_MakeViewToRead(&BUF_view, &buf);
  EXPECT_TRUE(memcmp(BUF_view.data, buf.data, DATA_SIZE) == 0);
  EXPECT_EQ(BUF_view.size, DATA_SIZE);
  EXPECT_EQ(BUF_view.read_index, 0);
  EXPECT_EQ(BUF_view.write_index, DATA_SIZE);
}

/**
 * \brief Make buffer view, 1 data read
 */
TEST_F(BUF_MakeViewToRead_Fixture, make_view_to_read_002)
{
  BUF_t BUF_view;
  BUF_ReadUint8(&buf);

  BUF_MakeViewToRead(&BUF_view, &buf);
  EXPECT_TRUE(memcmp(BUF_view.data, buf.data + 1, DATA_SIZE - 1) == 0);
  EXPECT_EQ(BUF_view.size, DATA_SIZE - 1);
  EXPECT_EQ(BUF_view.read_index, 0);
  EXPECT_EQ(BUF_view.write_index, DATA_SIZE - 1);
}

/**
 * \brief Make buffer view, 4 written, 1 data read
 */
TEST_F(BUF_MakeViewToRead_Fixture, make_view_to_read_003)
{
  BUF_InitEmpty(&buf, data, DATA_SIZE);
  BUF_WriteUint8(&buf, 0x01);
  BUF_WriteUint8(&buf, 0x02);
  BUF_WriteUint8(&buf, 0x03);
  BUF_WriteUint8(&buf, 0x04);
  BUF_ReadUint8(&buf);

  BUF_t BUF_view;
  BUF_MakeViewToRead(&BUF_view, &buf);
  EXPECT_TRUE(memcmp(BUF_view.data, buf.data + 1, DATA_SIZE - 1) == 0);
  EXPECT_EQ(BUF_view.size, 3);
  EXPECT_EQ(BUF_view.read_index, 0);
  EXPECT_EQ(BUF_view.write_index, 3);
}
