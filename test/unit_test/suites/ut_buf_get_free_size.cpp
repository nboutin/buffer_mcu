//! \file ut_BUF_get_free_size.cpp
//! \brief Buffer unit test
//! \date  2022/09
//! \author Nicolas Boutin
//! \copyright (C) Copyright Marelli 2022

#include <gtest/gtest.h>

extern "C" {
#include "buffer/buffer.h"
}

using namespace testing;

class BUF_GetFreeSize_Fixture : public ::testing::Test
{
protected:
  void SetUp()
  {}
  // attributes
  BUF_t buf;
  static constexpr uint8_t DATA_SIZE = 5;
  std::uint8_t data[DATA_SIZE];
};

/**
 * \brief Get free size on empty buffer
 */
TEST_F(BUF_GetFreeSize_Fixture, get_free_size_001)
{
  BUF_InitEmpty(&buf, data, DATA_SIZE);
  BUF_size_t free_size = BUF_GetFreeSize(&buf);
  EXPECT_EQ(free_size, DATA_SIZE);
}

/**
 * \brief Get free size on full buffer
 */
TEST_F(BUF_GetFreeSize_Fixture, get_free_size_002)
{
  BUF_InitFull(&buf, data, DATA_SIZE);
  BUF_size_t free_size = BUF_GetFreeSize(&buf);
  EXPECT_EQ(free_size, 0);
}

/**
 * \brief Get free size on buffer with one byte written
 */
TEST_F(BUF_GetFreeSize_Fixture, get_free_size_003)
{
  BUF_InitEmpty(&buf, data, DATA_SIZE);
  BUF_WriteUint8(&buf, 0x01);
  BUF_size_t free_size = BUF_GetFreeSize(&buf);
  EXPECT_EQ(free_size, DATA_SIZE - 1);
}

/**
 * \brief Get free size on buffer with one byte written and one byte read
 */
TEST_F(BUF_GetFreeSize_Fixture, get_free_size_004)
{
  BUF_InitEmpty(&buf, data, DATA_SIZE);
  BUF_WriteUint8(&buf, 0x01);
  BUF_ReadUint8(&buf);
  BUF_size_t free_size = BUF_GetFreeSize(&buf);
  EXPECT_EQ(free_size, DATA_SIZE - 1);
}
