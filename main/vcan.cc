#include "vcan.h"
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

Vcan::Vcan(const std::string &vcanId) : vcanId(vcanId), sockFd(-1), initSuccess(false) {
  initSuccess = Init();
}

bool Vcan::Init() {
  sockFd = socket(PF_CAN, SOCK_RAW, CAN_RAW);  // 创建socket
  if (sockFd == -1) {
    perror("socket");
    return false;
  }

  struct ifreq ifr;
  strcpy(ifr.ifr_name, vcanId.c_str());  // 绑定can0接口
  if (ioctl(sockFd, SIOCGIFINDEX, &ifr) == -1) {
    perror("ioctl");
    return false;
  }

  struct sockaddr_can addr;
  addr.can_family = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;

  if (bind(sockFd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {  // 绑定socket
    perror("bind");
    return false;
  }

  return true;
}

CanMsg Vcan::Receive() const{
  CanMsg canMsg(0x0, {0x0});
  if (initSuccess) {
    if (read(sockFd, (can_frame *)&canMsg, sizeof(canMsg)) != sizeof(canMsg)) {
      perror("Write error");
    }
  }
  return canMsg;
}

bool Vcan::Send(const CanMsg &msg) const {
  if (!initSuccess) {
    return false;
  }
  if (write(sockFd, (can_frame *)&msg, sizeof(msg)) != sizeof(msg)) {
    perror("Write error");
    return false;
  }
  return true;
}
