#ifndef B48CAFD598834461BBE25237D2C2C29D_H
#define B48CAFD598834461BBE25237D2C2C29D_H

#include <array>
#include "can_msg.h"
#include "can_receiver.h"
#include "can_sender.h"

struct McuUpdater {
  McuUpdater(CanSender &, CanReceiver &);

 public:
  bool Update(EcuAddr addr, const HexBin &bin);

 private:
  CanSender &sender;
  CanReceiver &receiver;
};

#endif
