#include "fota_server.h"
#include <chrono>
#include <future>
#include <iostream>
#include <thread>
#include "log.h"

FotaServer &FotaServer::GetInstance() {
  static FotaServer fotaServer;
  return fotaServer;
}

FotaServer::FotaServer() : runningFlag(false) {}

void FotaServer::ReceiveBin(const EcuBin &ecuBin) {
  std::lock_guard<std::mutex> lock(mtx);
  auto iter = updateEcus.find(ecuBin.GetAddr());
  if (iter != updateEcus.end()) {
    iter->second->updatingBin = ecuBin.GetBin();
  }
}

void FotaServer::UpdateBinDone(const EcuBin &ecuBin) {
  std::lock_guard<std::mutex> lock(mtx);
  auto iter = updateEcus.find(ecuBin.GetAddr());
  if (iter != updateEcus.end()) {
    iter->second->runningBin = ecuBin.GetBin();
  }
}

EcuBin FotaServer::PendingUpdateEcuBin() {
  std::lock_guard<std::mutex> lock(mtx);
  for (auto &iter : updateEcus) {
    if (iter.second->isNeedUpdate()) {
      return EcuBin{iter.first, iter.second->updatingBin};
    }
  }
  return EcuBin();
}

FotaServer &FotaServer::RegistEcu(EcuAddr addr, const EcuUpdater &updater) {
  ecuUpdaters.emplace(addr, &updater);
  {
    std::lock_guard<std::mutex> lock(mtx);
    updateEcus.emplace(addr, new EcuUpdateState{HexBin{0x0, 0x0}, HexBin{0x0, 0x0}});
  }
  return *this;
}

void FotaServer::Start() {
  auto fotaTask = [this]() {
    runningFlag.store(true);
    while (runningFlag.load()) {
      auto ecuBin = PendingUpdateEcuBin();
      if (!ecuBin.IsValid()) {
        if (ecuUpdaters.at(ecuBin.GetAddr())->Update(ecuBin)) {
          UpdateBinDone(ecuBin);
        }
      } else {
        std::cout << "FotaServer is running has no update ecu bin..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
      }
    }
    return true;
  };
  taskResult = std::async(std::launch::async, fotaTask);
}

bool FotaServer::Stop() {
  runningFlag.store(false);
  return taskResult.get();
}
