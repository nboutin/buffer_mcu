//! \file ut_buf_get_read_write.cpp
//! \brief Buffer unit test
//! \date  2024-04
//! \author Nicolas Boutin

#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include "buffer/buffer.h"
}

using namespace testing;
using ::testing::ElementsAreArray;
using ::testing::Each;

class BUF_GetReadWrite_UT : public ::testing::Test
{
protected:
  void SetUp()
  {}
  // attributes
  BUF_t buf;
  std::vector<std::uint8_t> data;
};

TEST_F(BUF_GetReadWrite_UT, GetUint8_001)
{
  data = {0xAA, 0xBB, 0xCC};
  BUF_InitFull(&buf, data.data(), data.size());

  auto value = BUF_GetUint8(&buf, 0);
  EXPECT_EQ(value, 0xAA);

  value = BUF_GetUint8(&buf, 1);
  EXPECT_EQ(value, 0xBB);

  value = BUF_GetUint8(&buf, 2);
  EXPECT_EQ(value, 0xCC);

  value = BUF_GetUint8(&buf, 3);
  EXPECT_EQ(value, 0x00);
}

TEST_F(BUF_GetReadWrite_UT, GetUint16_001)
{
  data = {0xAA, 0xBB, 0xCC, 0xDD};
  BUF_InitFull(&buf, data.data(), data.size());

  auto value = BUF_GetUint16(&buf, 0);
  EXPECT_EQ(value, 0xAABB);

  value = BUF_GetUint16(&buf, 1);
  EXPECT_EQ(value, 0xBBCC);

  value = BUF_GetUint16(&buf, 2);
  EXPECT_EQ(value, 0xCCDD);

  value = BUF_GetUint16(&buf, 3);
  EXPECT_EQ(value, 0);
}

TEST_F(BUF_GetReadWrite_UT, GetUint32_001)
{
  data = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
  BUF_InitFull(&buf, data.data(), data.size());

  auto value = BUF_GetUint32(&buf, 0);
  EXPECT_EQ(value, 0xAABBCCDD);

  value = BUF_GetUint32(&buf, 1);
  EXPECT_EQ(value, 0xBBCCDDEE);

  value = BUF_GetUint32(&buf, 2);
  EXPECT_EQ(value, 0xCCDDEEFF);

  value = BUF_GetUint32(&buf, 3);
  EXPECT_EQ(value, 0);
}

/**
 * \brief Get last uint8 data
 */
TEST_F(BUF_GetReadWrite_UT, GetLastUint8_001)
{
  data = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
  BUF_InitFull(&buf, data.data(), data.size());

  EXPECT_EQ(BUF_GetLastUint8(&buf), 0xFF);
}

/**
 * \brief Read uint8 data
 */
TEST_F(BUF_GetReadWrite_UT, ReadUint8_001)
{
  data = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
  BUF_InitFull(&buf, data.data(), data.size());

  EXPECT_EQ(BUF_ReadUint8(&buf), 0xAA);
  EXPECT_EQ(BUF_ReadUint8(&buf), 0xBB);
  EXPECT_EQ(BUF_ReadUint8(&buf), 0xCC);
  EXPECT_EQ(BUF_ReadUint8(&buf), 0xDD);
  EXPECT_EQ(BUF_ReadUint8(&buf), 0xEE);
  EXPECT_EQ(BUF_ReadUint8(&buf), 0xFF);
  EXPECT_EQ(BUF_ReadUint8(&buf), 0x00);

  EXPECT_EQ(BUF_ReadUint8(nullptr), 0x00);

  BUF_InitEmpty(&buf, data.data(), data.size());
  EXPECT_EQ(BUF_ReadUint8(nullptr), 0x00);
}

/**
 * \brief Read uint16 data
 */
TEST_F(BUF_GetReadWrite_UT, ReadUint16_001)
{
  data = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
  BUF_InitFull(&buf, data.data(), data.size());

  EXPECT_EQ(BUF_ReadUint16(&buf), 0xAABB);
  EXPECT_EQ(BUF_ReadUint16(&buf), 0xCCDD);
  EXPECT_EQ(BUF_ReadUint16(&buf), 0xEEFF);
  EXPECT_EQ(BUF_ReadUint16(&buf), 0x0000);

  EXPECT_EQ(BUF_ReadUint16(nullptr), 0x0000);

  BUF_InitEmpty(&buf, data.data(), data.size());
  EXPECT_EQ(BUF_ReadUint16(nullptr), 0x0000);
}

/**
 * \brief Read uint32 data
 */
TEST_F(BUF_GetReadWrite_UT, ReadUint32_001)
{
  data = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11, 0x22, 0x33};
  BUF_InitFull(&buf, data.data(), data.size());

  EXPECT_EQ(BUF_ReadUint32(&buf), 0xAABBCCDD);
  EXPECT_EQ(BUF_ReadUint32(&buf), 0xEEFF1122);

  EXPECT_EQ(BUF_ReadUint32(nullptr), 0x00000000);

  BUF_InitEmpty(&buf, data.data(), data.size());
  EXPECT_EQ(BUF_ReadUint32(nullptr), 0x00000000);
}

/**
 * \brief Write uint8 data
 */
TEST_F(BUF_GetReadWrite_UT, WriteUint8_001)
{
  data = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
  BUF_InitEmpty(&buf, data.data(), data.size());

  EXPECT_EQ(BUF_WriteUint8(&buf, 0x11), 1);
  EXPECT_EQ(BUF_WriteUint8(&buf, 0x22), 1);
  EXPECT_EQ(BUF_WriteUint8(&buf, 0x33), 1);
  EXPECT_EQ(BUF_WriteUint8(&buf, 0x44), 1);
  EXPECT_EQ(BUF_WriteUint8(&buf, 0x55), 1);
  EXPECT_EQ(BUF_WriteUint8(&buf, 0x66), 1);

  std::vector<std::uint8_t> expected = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
  EXPECT_TRUE(memcmp(buf.data, expected.data(), buf.size) == 0);

  EXPECT_EQ(BUF_WriteUint8(nullptr, 0x00), 0);

  buf.data = nullptr;
  EXPECT_EQ(BUF_WriteUint8(&buf, 0x00), 0);

  data = {};
  BUF_InitEmpty(&buf, data.data(), data.size());
  EXPECT_EQ(BUF_WriteUint8(&buf, 0x00), 0);
}

/**
 * \brief Write uint16 data
 */
TEST_F(BUF_GetReadWrite_UT, WriteUint16_001)
{
  data = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
  BUF_InitEmpty(&buf, data.data(), data.size());

  EXPECT_EQ(BUF_WriteUint16(&buf, 0x1122), 2);
  EXPECT_EQ(BUF_WriteUint16(&buf, 0x3344), 2);
  EXPECT_EQ(BUF_WriteUint16(&buf, 0x5566), 2);

  std::vector<std::uint8_t> expected = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
  EXPECT_TRUE(memcmp(buf.data, expected.data(), buf.size) == 0);

  EXPECT_EQ(BUF_WriteUint16(nullptr, 0x0000), 0);

  data = {};
  BUF_InitEmpty(&buf, data.data(), data.size());
  EXPECT_EQ(BUF_WriteUint16(&buf, 0x0000), 0);
}

/**
 * \brief Write uint32 data
 */
TEST_F(BUF_GetReadWrite_UT, WriteUint32_001)
{
  data = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11, 0x22};
  BUF_InitEmpty(&buf, data.data(), data.size());

  EXPECT_EQ(BUF_WriteUint32(&buf, 0x11223344), 4);
  EXPECT_EQ(BUF_WriteUint32(&buf, 0x55667788), 4);

  std::vector<std::uint8_t> expected = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
  EXPECT_TRUE(memcmp(buf.data, expected.data(), buf.size) == 0);

  EXPECT_EQ(BUF_WriteUint32(nullptr, 0x00000000), 0);

  data = {};
  BUF_InitEmpty(&buf, data.data(), data.size());
  EXPECT_EQ(BUF_WriteUint32(&buf, 0x00000000), 0);
}

/**
 * \brief Write uint64 data
 */
TEST_F(BUF_GetReadWrite_UT, WriteUint64_001)
{
  data = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11, 0x22};
  BUF_InitEmpty(&buf, data.data(), data.size());

  EXPECT_EQ(BUF_WriteUint64(&buf, 0x1122334455667788), 8);

  std::vector<std::uint8_t> expected = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
  EXPECT_TRUE(memcmp(buf.data, expected.data(), buf.size) == 0);

  EXPECT_EQ(BUF_WriteUint64(nullptr, 0x0000000000000000), 0);

  data = {};
  BUF_InitEmpty(&buf, data.data(), data.size());
  EXPECT_EQ(BUF_WriteUint64(&buf, 0x0000000000000000), 0);
}

/**
 * \brief Write raw data
 */
TEST_F(BUF_GetReadWrite_UT, WriteRaw_001)
{
  data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  BUF_InitEmpty(&buf, data.data(), data.size());

  std::vector<std::uint8_t> raw = {0x11, 0x22, 0x33, 0x44};
  EXPECT_EQ(BUF_WriteRaw(&buf, raw.data(), raw.size()), raw.size());

  std::vector<std::uint8_t> expected = {0x11, 0x22, 0x33, 0x44, 0x00, 0x00};
  EXPECT_TRUE(memcmp(buf.data, expected.data(), buf.size) == 0);

  EXPECT_EQ(BUF_WriteRaw(nullptr, raw.data(), raw.size()), 0);
  EXPECT_EQ(BUF_WriteRaw(&buf, nullptr, raw.size()), 0);
  EXPECT_EQ(BUF_WriteRaw(nullptr, nullptr, raw.size()), 0);
  EXPECT_EQ(BUF_WriteRaw(&buf, raw.data(), 0), 0);
  EXPECT_EQ(BUF_WriteRaw(nullptr, raw.data(), 0), 0);
  EXPECT_EQ(BUF_WriteRaw(&buf, nullptr, 0), 0);
  EXPECT_EQ(BUF_WriteRaw(nullptr, nullptr, 0), 0);

  data = {};
  BUF_InitEmpty(&buf, data.data(), data.size());
  EXPECT_EQ(BUF_WriteRaw(&buf, raw.data(), raw.size()), 0);
}

/**
 * \brief Write string data
 */
TEST_F(BUF_GetReadWrite_UT, WriteString_001)
{
  data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0X00};
  BUF_InitEmpty(&buf, data.data(), data.size());

  std::string str = "Hello";
  EXPECT_EQ(BUF_WriteString(&buf, str.c_str(), str.size()), str.size());

  std::vector<std::uint8_t> expected = {'H', 'e', 'l', 'l', 'o'};
  EXPECT_THAT(expected, ElementsAreArray(buf.data, expected.size()));
}

/**
 * \brief GetData
 */
TEST_F(BUF_GetReadWrite_UT, GetData_001)
{
  data = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
  BUF_InitEmpty(&buf, data.data(), data.size());

  const std::uint8_t* BUF_data = BUF_GetData(&buf);
  EXPECT_EQ(data.data(), BUF_data);
  EXPECT_EQ(BUF_GetData(nullptr), nullptr);
}

/**
 * \brief GetDataNoConst
 */
TEST_F(BUF_GetReadWrite_UT, GetDataNoConst_001)
{
  data = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
  BUF_InitEmpty(&buf, data.data(), data.size());

  std::uint8_t* BUF_data = BUF_GetDataNoConst(&buf);
  EXPECT_EQ(data.data(), BUF_data);
  EXPECT_EQ(BUF_GetDataNoConst(nullptr), nullptr);
}
