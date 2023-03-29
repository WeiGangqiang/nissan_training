#include "sync_ecu_updater.h"
#include "ecu_bin.h"
#include "log.h"

SyncEcuUpdater::SyncEcuUpdater(const CanSender &sender, const CanReceiver &receiver) : sender(sender), receiver(receiver) {}

bool SyncEcuUpdater::Update(const EcuBin& ecuBin) const {
  CHECK_FALSE_RET(sender.Send(RequestDownload(ecuBin.GetAddr())), "send RequestDownload failed !");
  CHECK_FALSE_RET(receiver.Receive() == RequestDownloadRsp(ecuBin.GetAddr()), "receive RequestDownloadRsp failed !");
  CHECK_FALSE_RET(sender.Send(TransferData(ecuBin.GetAddr(), ecuBin.GetBin())), "send TransferData failed !");
  CHECK_FALSE_RET(receiver.Receive() == TransferDataRsp(ecuBin.GetAddr()), "send TransferData failed !");

  CHECK_FALSE_RET(sender.Send(EndRequest(ecuBin.GetAddr())), "send EndRequest failed !");
  CHECK_FALSE_RET(receiver.Receive() == EndRequestRsp(ecuBin.GetAddr()), "receive EndRequestRsp failed !");
  return true;
}