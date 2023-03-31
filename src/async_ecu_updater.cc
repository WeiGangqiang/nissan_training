#include "async_ecu_updater.h"
#include "sync_ecu_updater.h"
#include "ecu_bin.h"

#include <future>

AsyncEcuUpdater::AsyncEcuUpdater(const SyncEcuUpdater &updater) : updater(updater) {}

bool AsyncEcuUpdater::Update(const EcuBin &ecuBin) const {
  std::future<bool> fut = std::async(std::launch::async, [this, ecuBin = ecuBin](){
      return updater.Update(ecuBin);
  });

  return fut.get();
}
