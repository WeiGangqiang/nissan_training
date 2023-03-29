#include "can_msg.h"

CanMsg::CanMsg(CanID canId, std::initializer_list<uint8_t> values) {
  std::memset(data, 0, sizeof(data));
  if (values.size() > MAX_DLC_LENGTH) {
    return;
  }
  can_id = canId;
  can_dlc = values.size();
  __pad = 0;
  __res0 = 0;
  __res1 = 0;
  size_t idx = 0;
  for (auto value : values) {
    data[idx++] = value;
  }
}

bool CanMsg::operator==(const CanMsg &lft) const {
  return this->GetID() == lft.GetID() && this->GetLength() == lft.GetLength() &&
         (memcmp(data, lft.data, lft.GetLength()) == 0);
}

bool CanMsg::operator!=(const CanMsg &lft) const {
  return !((*this) == lft);
}
