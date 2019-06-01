#include "switchcmd.h"

SwitchCMD::SwitchCMD(const Device * const device, Device::SwitchValue switchValue) :
    CMD(device),
    switchValue_(switchValue)
{
    
}

QString SwitchCMD::toQStringCMD() const
{
    // 发送“设备类型 设备号 值”
    QString output;
    output.append(CMD::startDelimiter_);
    output.append(QString("%1 %2 %3")
                  .arg(static_cast<int>(this->device_->deviceType()))
                  .arg(static_cast<int>(this->device_->deviceId()))
                  .arg(static_cast<int>(this->switchValue_)));
    output.append(CMD::stopDelimiter_);
    
    return output;
}
