#include "device.h"


Device::Device(Device::DeviceType deviceType, Device::DeviceId deviceId, QObject *device) : 
    deviceType_(deviceType),
    deviceId_(deviceId),
    device_(device)
{
    
}

Device::~Device()
{
    
}

Device::DeviceType Device::deviceType() const
{
    return deviceType_;
}

void Device::setDeviceType(const DeviceType &deviceType)
{
    deviceType_ = deviceType;
}

Device::DeviceId Device::deviceId() const
{
    return deviceId_;
}

void Device::setDeviceId(const DeviceId &deviceId)
{
    deviceId_ = deviceId;
}

QObject *Device::device() const
{
    return device_;
}

void Device::setDevice(QObject *device)
{
    device_ = device;
}

void Device::executeCMD()
{
    
}

void Device::executeCMD(Device::SwitchValue)
{
    
}

void Device::executeCMD(double)
{
    
}

void Device::executeCMD(const QString &)
{
    
}
