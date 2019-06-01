#include "switchdevice.h"

SwitchDevice::SwitchDevice(DeviceId deviceId, QObject *device) : 
    Device(Device::DeviceType::SwitchType, deviceId, device)
{
    
}
