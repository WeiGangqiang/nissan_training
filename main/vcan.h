#ifndef INC_5389AD1ABAEC40079CB0E7192C5D0627_H
#define INC_5389AD1ABAEC40079CB0E7192C5D0627_H

#include "can_receiver.h"
#include "can_sender.h"

struct Vcan : public CanSender, CanReceiver {
  Vcan(const std::string &);

 private:
  CanMsg Receive() const override;
  bool Send(const CanMsg &msg) const override;

 private:
  bool Init();

 private:
  std::string  vcanId;
  int sockFd;
  bool initSuccess;
};

#endif
