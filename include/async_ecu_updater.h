#ifndef INC_2EA1CCB6B4B042C9AB843C59A5DBC8E8_H
#define INC_2EA1CCB6B4B042C9AB843C59A5DBC8E8_H

#include "ecu_updater.h"

struct SyncEcuUpdater;

struct AsyncEcuUpdater : public EcuUpdater {
  AsyncEcuUpdater(const SyncEcuUpdater &);

 private:
  bool Update(const EcuBin &ecuBin) const override;

 private:
  const EcuUpdater &updater;
};

#endif
