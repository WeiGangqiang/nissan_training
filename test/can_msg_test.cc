#include "gtest/gtest.h"
#include "can_msg.h"
#include <functional>
#include <list>
class CanMsgTest : public testing::Test {};

TEST(CanMsgTest, test_can_msg_construct_success) {
  auto msg = CanMsg(0x21, {0x3, 0x4});
  ASSERT_EQ(msg.GetLength(), 2);
  ASSERT_EQ(msg.GetID(), 0x21);
}

TEST(CanMsgTest, test_can_msg_compare_success) {
  ASSERT_EQ(RequestDownload(0x01), RequestDownload(0x01));
  ASSERT_NE(RequestDownload(0x01), RequestDownload(0x02));
  ASSERT_NE(RequestDownload(0x01), TransferData(0x01, {0x01, 0x01}));
  ASSERT_NE(RequestDownload(0x01), RequestDownloadRsp(0x01));
}
