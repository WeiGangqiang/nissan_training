#ifndef INC_109A1625D147458EBF97BE2FBBD64FFA_H
#define INC_109A1625D147458EBF97BE2FBBD64FFA_H

struct CanMsg;

struct CanSender {
  virtual bool Send(const CanMsg &msg) = 0;
  virtual ~CanSender() {}
};

#endif
