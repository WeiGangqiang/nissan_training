#ifndef INC_7EB71A02B84C4DE58516DFFCDF1549DA_H
#define INC_7EB71A02B84C4DE58516DFFCDF1549DA_H

#include <array>
#include "ecu_addr.h"

using HexBin = std::array<uint8_t, 2>;

struct EcuBin {
  EcuBin(const EcuAddr ecuAddr = 0x0, const HexBin &hexbin = HexBin{0x0,0x0}) : ecuAddr(ecuAddr), hexBin(hexbin) {}

  EcuAddr GetAddr() const {
    return ecuAddr;
  }
  const HexBin &GetBin() const {
    return hexBin;
  }

  bool IsValid() const {
    return ecuAddr == 0 && hexBin[0] == 0 && hexBin[1] == 0;
  }

 private:
  EcuAddr ecuAddr;
  HexBin hexBin;
};

#endif
