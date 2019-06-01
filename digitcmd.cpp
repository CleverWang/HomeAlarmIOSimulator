#include "digitcmd.h"

DigitCMD::DigitCMD(Device * device, double digitValue) :
    CMD(device),
    digitValue_(digitValue)
{
    
}

QString DigitCMD::toQStringCMD() const
{
    // 发送“设备类型 设备号 值”
    QString output;
    output.append(CMD::startDelimiter_);
    output.append(QString("%1 %2 %3")
                  .arg(static_cast<int>(this->device_->deviceType()))
                  .arg(static_cast<int>(this->device_->deviceId()))
                  .arg(this->digitValue_));
    output.append(CMD::stopDelimiter_);
    
    return output;
}
