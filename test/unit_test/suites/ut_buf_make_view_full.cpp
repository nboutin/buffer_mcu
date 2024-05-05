//! \file ut_buf_make_view_full.cpp
//! \brief Buffer unit test
//! \date  2024-04
//! \author Nicolas Boutin

#include <gtest/gtest.h>

extern "C" {
#include "buffer/buffer.h"
}

using namespace testing;

class BUF_MakeViewFull_Fixture : public ::testing::Test
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
 * \brief Make buffer view on whole buffer
 */
TEST_F(BUF_MakeViewFull_Fixture, make_view_full_001)
{
  BUF_t BUF_view;
  BUF_MakeViewFull(&BUF_view, &buf, 0, DATA_SIZE);
  EXPECT_EQ(BUF_view.data, buf.data);
  EXPECT_EQ(BUF_view.size, DATA_SIZE);
  EXPECT_EQ(BUF_view.read_index, 0);
  EXPECT_EQ(BUF_view.write_index, DATA_SIZE);
}

/**
 * \brief Make buffer view on buffer index 1 to end
 */
TEST_F(BUF_MakeViewFull_Fixture, make_view_full_002)
{
  BUF_t BUF_view;
  static constexpr uint8_t VIEW_SIZE = 4;
  BUF_MakeViewFull(&BUF_view, &buf, 1, VIEW_SIZE);
  EXPECT_EQ(BUF_view.size, VIEW_SIZE);
  EXPECT_EQ(BUF_view.read_index, 0);
  EXPECT_EQ(BUF_view.write_index, VIEW_SIZE);
}

/**
 * \brief Make buffer view on buffer from start to end -1
*/
TEST_F(BUF_MakeViewFull_Fixture, make_view_full_003)
{
  BUF_t BUF_view;
  static constexpr uint8_t VIEW_SIZE = 4;
  BUF_MakeViewFull(&BUF_view, &buf, 0, VIEW_SIZE);
  EXPECT_EQ(BUF_view.size, VIEW_SIZE);
  EXPECT_EQ(BUF_view.read_index, 0);
  EXPECT_EQ(BUF_view.write_index, VIEW_SIZE);
}

/**
 * \brief Make buffer view on buffer from index 1 to end -1
*/
TEST_F(BUF_MakeViewFull_Fixture, make_view_full_004)
{
  BUF_t BUF_view;
  static constexpr uint8_t VIEW_SIZE = 3;
  BUF_MakeViewFull(&BUF_view, &buf, 1, VIEW_SIZE);
  EXPECT_EQ(BUF_view.size, VIEW_SIZE);
  EXPECT_EQ(BUF_view.read_index, 0);
  EXPECT_EQ(BUF_view.write_index, VIEW_SIZE);
}
