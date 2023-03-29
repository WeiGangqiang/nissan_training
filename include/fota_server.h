#ifndef D2A88BAF7DB646A5A5E5A0DBCA78D87D_H
#define D2A88BAF7DB646A5A5E5A0DBCA78D87D_H

#include <atomic>
#include <future>
#include <memory>
#include <mutex>
#include <unordered_map>
#include "ecu_bin.h"
#include "ecu_updater.h"

struct FotaServer {
  static FotaServer &GetInstance();
  void ReceiveBin(const EcuBin &);
  void Start();
  bool Stop();
  FotaServer &RegistEcu(EcuAddr, const EcuUpdater &);

 private:
  FotaServer();
  void UpdateBinDone(const EcuBin &);
  EcuBin PendingUpdateEcuBin();

 private:
  struct EcuUpdateState {
    HexBin updatingBin;
    HexBin runningBin;
    bool isNeedUpdate() const {
      return runningBin == updatingBin;
    }
  };
  using EcuUpdateStatePtr = std::unique_ptr<EcuUpdateState>;

 private:
  std::mutex mtx;
  std::unordered_map<EcuAddr, EcuUpdateStatePtr> updateEcus;
  std::unordered_map<EcuAddr, const EcuUpdater *> ecuUpdaters;
  std::atomic<bool> runningFlag;
  std::future<bool> taskResult;
};

#endif
