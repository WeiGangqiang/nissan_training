#include "gtest/gtest.h"
#include <functional>
#include <list>
#include <deque>
#include "can_msg.h"
#include "ecu_bin.h"
#include "ecu_updater.h"
#include "sync_ecu_updater.h"
#include "can_sender.h"
#include "can_receiver.h"

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
  CanMsg Receive() const override {
    if (sendMsgs.empty()) {
      return CanMsg{0x00, {0x00}};
    }
    auto msg = sendMsgs.front();
    sendMsgs.pop_front();
    return msg;
  }
  bool Send(const CanMsg &msg) const override {
    if (checkers.empty()) {
      return false;
    }
    auto checker = checkers.front();
    checkers.pop_front();
    checker(msg);
    return true;
  }

 private:
  mutable std::list<MsgChecker> checkers;
  mutable std::deque<CanMsg> sendMsgs;
};

#define RECV(...) ExpectRecv([&](const CanMsg &msg) __VA_ARGS__);
#define SEND(...) ExpectSend(__VA_ARGS__)

}  // namespace

class EcuUpdaterTest : public testing::Test {};

TEST(EcuUpdaterTest, test_request) {
  constexpr EcuAddr bcm_addr = 0x03;
  constexpr HexBin  bcm_bin = {0x01, 0x02};
  FakeMcu bcm;

  bcm.RECV({ ASSERT_EQ(msg, RequestDownload(bcm_addr)); });

  bcm.SEND(RequestDownloadRsp(bcm_addr));

  bcm.RECV({ ASSERT_EQ(msg, TransferData(bcm_addr, bcm_bin)); });

  bcm.SEND(TransferDataRsp(bcm_addr));

  bcm.RECV({ ASSERT_EQ(msg, EndRequest(bcm_addr)); });

  bcm.SEND(EndRequestRsp(bcm_addr));

  const SyncEcuUpdater syncUpdater(bcm, bcm);
  ASSERT_TRUE(static_cast<const EcuUpdater &>(syncUpdater).Update(EcuBin(bcm_addr, bcm_bin)));
}

