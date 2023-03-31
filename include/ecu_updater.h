#ifndef E407F3392ABB4222862568CABB641CEB_H
#define E407F3392ABB4222862568CABB641CEB_H

#include <array>
#include <memory>

struct EcuBin;

struct EcuUpdater {
  virtual bool Update(const EcuBin& ecuBin) const = 0;
  virtual ~EcuUpdater() {}
};


#endif
