#include "gtest/gtest.h"
#include <functional>
#include <list>
#include "fota_server.h"


class FotaServerTest : public testing::Test {};


TEST(FotaServerTest, test_fota_server_runing_success_without_regist_ecu){
  auto& fotoServer = FotaServer::GetInstance();
  fotoServer.Start();
  std::this_thread::sleep_for(std::chrono::seconds(5));
  ASSERT_TRUE(fotoServer.Stop());
}

TEST(FotaServerTest, test_fota_server_runing_success_with_regist_one_ecu){
  auto& fotoServer = FotaServer::GetInstance();
  fotoServer.Start();
  std::this_thread::sleep_for(std::chrono::seconds(5));
  ASSERT_TRUE(fotoServer.Stop());
}

