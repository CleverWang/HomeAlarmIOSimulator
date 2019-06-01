#include "stringdevice.h"

StringDevice::StringDevice(DeviceId deviceId, QObject *device) :
    Device (Device::DeviceType::StringType, deviceId, device)
{
    
}
