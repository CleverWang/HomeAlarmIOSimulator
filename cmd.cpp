#include "cmd.h"

QString CMD::startDelimiter_ = ">";
QString CMD::stopDelimiter_ = "<";

QString CMD::startDelimiter()
{
    return startDelimiter_;
}

void CMD::setStartDelimiter(const QString &startDelimiter)
{
    startDelimiter_ = startDelimiter;
}

QString CMD::stopDelimiter()
{
    return stopDelimiter_;
}

void CMD::setStopDelimiter(const QString &stopDelimiter)
{
    stopDelimiter_ = stopDelimiter;
}

CMD::CMD(Device::DeviceType deviceType, Device::DeviceId deviceId) : 
    deviceType_(deviceType),
    deviceId_(deviceId), 
    switchValue_(Device::SwitchValue::UnknownSwitchValue),
    digitValue_(UnknownDigitValue),
    stringValue_()
{
    
}

CMD::CMD(Device::DeviceType deviceType, Device::DeviceId deviceId, Device::SwitchValue switchValue) : 
    deviceType_(deviceType),
    deviceId_(deviceId), 
    switchValue_(switchValue),
    digitValue_(UnknownDigitValue),
    stringValue_()
{
    
}

CMD::CMD(Device::DeviceType deviceType, Device::DeviceId deviceId, double digitValue) : 
    deviceType_(deviceType),
    deviceId_(deviceId), 
    switchValue_(Device::SwitchValue::UnknownSwitchValue),
    digitValue_(digitValue),
    stringValue_()
{
    
}

CMD::CMD(Device::DeviceType deviceType, Device::DeviceId deviceId, const QString &stringValue) : 
    deviceType_(deviceType),
    deviceId_(deviceId), 
    switchValue_(Device::SwitchValue::UnknownSwitchValue),
    digitValue_(UnknownDigitValue),
    stringValue_(stringValue)
{
    
}

Device::DeviceType CMD::deviceType() const
{
    return deviceType_;
}

void CMD::setDeviceType(const Device::DeviceType &deviceType)
{
    deviceType_ = deviceType;
}

Device::DeviceId CMD::deviceId() const
{
    return deviceId_;
}

void CMD::setDeviceId(const Device::DeviceId &deviceId)
{
    deviceId_ = deviceId;
}

Device::SwitchValue CMD::switchValue() const
{
    return switchValue_;
}

void CMD::setSwitchValue(const Device::SwitchValue &switchValue)
{
    switchValue_ = switchValue;
}

double CMD::digitValue() const
{
    return digitValue_;
}

void CMD::setDigitValue(double digitValue)
{
    digitValue_ = digitValue;
}

QString CMD::stringValue() const
{
    return stringValue_;
}

void CMD::setStringValue(const QString &stringValue)
{
    stringValue_ = stringValue;
}

QString CMD::toString() const
{
    QString output;
    output.append(CMD::startDelimiter_);
    switch (this->deviceType_) 
    {
    case Device::DeviceType::KeyType:
        output.append(QString("%1 %2")
                      .arg(static_cast<int>(this->deviceType_))
                      .arg(static_cast<int>(this->deviceId_)));
        break;
    case Device::DeviceType::SwitchType:
        output.append(QString("%1 %2 %3")
                      .arg(static_cast<int>(this->deviceType_))
                      .arg(static_cast<int>(this->deviceId_))
                      .arg(static_cast<int>(this->switchValue_)));
        break;
        
    case Device::DeviceType::DigitType:
        output.append(QString("%1 %2 %3")
                      .arg(static_cast<int>(this->deviceType_))
                      .arg(static_cast<int>(this->deviceId_))
                      .arg(this->digitValue_));
        break;
    case Device::DeviceType::StringType:
        output.append(QString("%1 %2 %3")
                      .arg(static_cast<int>(this->deviceType_))
                      .arg(static_cast<int>(this->deviceId_))
                      .arg(this->stringValue_));
        break;
    }
    output.append(CMD::stopDelimiter_);
    
    return output;
}
