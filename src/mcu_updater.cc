#include "mcu_updater.h"
#include "log.h"

McuUpdater::McuUpdater(CanSender &sender, CanReceiver &receiver) : sender(sender), receiver(receiver) {}

bool McuUpdater::Update(EcuAddr addr, const HexBin &bin) {
  CHECK_FALSE_RET(sender.Send(RequestDownload(addr)), "send RequestDownload failed !");
  CHECK_FALSE_RET(receiver.Receive() == RequestDownloadRsp(addr), "receive RequestDownloadRsp failed !");
  CHECK_FALSE_RET(sender.Send(TransferData(addr, bin)), "send TransferData failed !");
  CHECK_FALSE_RET(receiver.Receive() == TransferDataRsp(addr), "send TransferData failed !");

  CHECK_FALSE_RET(sender.Send(EndRequest(addr)), "send EndRequest failed !");
  CHECK_FALSE_RET(receiver.Receive() == EndRequestRsp(addr), "receive EndRequestRsp failed !");
  return true;
}
