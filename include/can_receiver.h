#ifndef INC_8DB8C9A07F484E94A7F9A6AF2B1ED7CA_H
#define INC_8DB8C9A07F484E94A7F9A6AF2B1ED7CA_H

#include "can_msg.h"

struct CanReceiver {
  virtual CanMsg Receive() = 0;
  virtual ~CanReceiver() {}
};

#endif
