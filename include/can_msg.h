#ifndef HFEC44BEF_BF84_42A9_B7F7_A99E99FE9006
#define HFEC44BEF_BF84_42A9_B7F7_A99E99FE9006

#include <linux/can.h>
#include <stdint.h>
#include <array>
#include <cstring>
#include <initializer_list>

using CanID = uint64_t;
using EcuAddr = uint8_t;
using HexBin = std::array<uint8_t, 2>;

struct CanMsg : private can_frame {
  CanMsg(CanID canId, std::initializer_list<uint8_t> values);
  CanID GetID() const {
    return can_id;
  }
  size_t GetLength() const {
    return can_dlc;
  }
  bool operator==(const CanMsg &) const;
  bool operator!=(const CanMsg &) const;

 private:
  constexpr static size_t MAX_DLC_LENGTH = 8;
};

struct RequestDownload:CanMsg{
  explicit RequestDownload(EcuAddr addr): CanMsg(0x7DF, {0x34, 0x02, addr}){}
};

struct RequestDownloadRsp:CanMsg{
  explicit RequestDownloadRsp(EcuAddr addr): CanMsg(0x7E8, {0x74, 0x01, addr}){}
};

struct TransferData : CanMsg {
  TransferData(EcuAddr addr, const HexBin &hex) : CanMsg(0x7E8, {0x36, 0x01, addr, hex[0], hex[1]}) {}
};

struct TransferDataRsp:CanMsg{
  explicit TransferDataRsp(EcuAddr addr): CanMsg(0x7E8, {0x76, 0x01,addr}){}
};

struct EndRequest:CanMsg{
  explicit EndRequest(EcuAddr addr): CanMsg(0x7DF, {0x10, 0x81, addr}){}
};

struct EndRequestRsp:CanMsg{
  explicit EndRequestRsp(EcuAddr addr): CanMsg(0x7DF, {0x50, addr}){}
};


#endif
