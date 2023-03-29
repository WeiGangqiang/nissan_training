#include "mcu_updater.h"
#include <functional>
#include <list>
#include "can_msg.h"
#include "gtest/gtest.h"

namespace {

class McuUpdaterTest : public testing::Test {};

TEST(McuUpdaterTest, test_can_msg_construct_success) {
  auto msg = CanMsg(0x21, {0x3, 0x4});
  ASSERT_EQ(msg.GetLength(), 2);
  ASSERT_EQ(msg.GetID(), 0x21);
}

TEST(McuUpdaterTest, test_can_msg_compare_success) {
  ASSERT_EQ(RequestDownload(0x01), RequestDownload(0x01));
  ASSERT_NE(RequestDownload(0x01), TransferData(0x01, {0x01, 0x01}));
  ASSERT_NE(RequestDownload(0x01), RequestDownloadRsp(0x01));
}

namespace {

using MsgChecker = std::function<void(const CanMsg &msg)>;

struct FakeMcu : public CanSender, CanReceiver {
  void ExpectRecv(const MsgChecker &checker) {
    checkers.emplace_back(checker);
  }
  void ExpectSend(const CanMsg &msg) {
    sendMsgs.emplace_back(msg);
  }

 private:
  CanMsg Receive() override {
    if (sendMsgs.empty()) {
      return CanMsg{0x00, {0x00}};
    }
    auto msg = sendMsgs.front();
    sendMsgs.pop_front();
    return msg;
  }
  bool Send(const CanMsg &msg) override {
    if (checkers.empty()) {
      return false;
    }
    auto checker = checkers.front();
    checkers.pop_front();
    checker(msg);
    return true;
  }

 private:
  std::list<MsgChecker> checkers;
  std::list<CanMsg> sendMsgs;
};

#define RECV(...) ExpectRecv([&](const CanMsg &msg) __VA_ARGS__);
#define SEND(...) ExpectSend(__VA_ARGS__)

}  // namespace


TEST(McuUpdaterTest, test_request) {
  constexpr EcuAddr bcm_addr = 0x03;
  constexpr HexBin  bcm_bin = {0x01, 0x02};
  FakeMcu bcm;

  bcm.RECV({ ASSERT_EQ(msg, RequestDownload(bcm_addr)); });

  bcm.SEND(RequestDownloadRsp(bcm_addr));

  bcm.RECV({ ASSERT_EQ(msg, TransferData(bcm_addr, bcm_bin)); });

  bcm.SEND(TransferDataRsp(bcm_addr));

  bcm.RECV({ ASSERT_EQ(msg, EndRequest(bcm_addr)); });

  bcm.SEND(EndRequestRsp(bcm_addr));

  ASSERT_TRUE(McuUpdater(bcm, bcm).Update(bcm_addr, bcm_bin));
}

}  // namespace
