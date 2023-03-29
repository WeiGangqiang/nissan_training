#include "fota_server.h"
#include <functional>
#include <list>
#include "gtest/gtest.h"

class FotaServerTest : public testing::Test {};

TEST(FotaServerTest, test_fota_server_runing_success_without_regist_ecu) {
  auto &fotoServer = FotaServer::GetInstance();
  fotoServer.Start();
  std::this_thread::sleep_for(std::chrono::seconds(5));
  ASSERT_TRUE(fotoServer.Stop());
}

namespace {

struct FakeEcuUpdater : EcuUpdater {
  bool Update(const EcuBin& ecuBin) const override{
    updateBin = ecuBin;
    return  true;
  }
  mutable EcuBin updateBin;
};

}  // namespace

TEST(FotaServerTest, test_fota_server_runing_success_with_regist_one_ecu) {
  auto &fotoServer = FotaServer::GetInstance();
  auto bcmBin = EcuBin{BCM, HexBin{0x1, 0x1}};
  FakeEcuUpdater fakeUpdater;
  fotoServer.RegistEcu(BCM, fakeUpdater);

  fotoServer.Start();
  fotoServer.ReceiveBin(bcmBin);

  std::this_thread::sleep_for(std::chrono::seconds(5));
  ASSERT_TRUE(fotoServer.Stop());

  ASSERT_EQ(fakeUpdater.updateBin.GetAddr(), bcmBin.GetAddr());
  ASSERT_EQ(fakeUpdater.updateBin.GetBin(), bcmBin.GetBin());

}
