#ifndef INC_565703E6E68A424C80856EEDB144D7B6_H
#define INC_565703E6E68A424C80856EEDB144D7B6_H

#include "ecu_updater.h"
#include "can_msg.h"
#include "can_receiver.h"
#include "can_sender.h"


struct SyncEcuUpdater: public EcuUpdater {
  SyncEcuUpdater(const CanSender &, const CanReceiver &);

 private:
  bool Update(const EcuBin& ecuBin) const override;

 private:
  const CanSender &sender;
  const CanReceiver &receiver;
};

#endif
