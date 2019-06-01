#include "stringcmd.h"

StringCMD::StringCMD(Device * device, const QString &stringValue) :
    CMD(device),
    stringValue_(stringValue)
{
    
}

QString StringCMD::toQStringCMD() const
{
    // 发送“设备类型 设备号 值”
    QString output;
    output.append(CMD::startDelimiter_);
    output.append(QString("%1 %2 %3")
                  .arg(static_cast<int>(this->device_->deviceType()))
                  .arg(static_cast<int>(this->device_->deviceId()))
                  .arg(this->stringValue_));
    output.append(CMD::stopDelimiter_);
    
    return output;
}

void StringCMD::execute()
{
    this->device_->executeCMD(this->stringValue_);
}
