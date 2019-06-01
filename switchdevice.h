#ifndef SWITCHDEVICE_H
#define SWITCHDEVICE_H

#include "device.h"

// 开关型设备基类
class SwitchDevice : public Device
{
public:
    SwitchDevice(DeviceId deviceId, QObject *device);
};

#endif // SWITCHDEVICE_H
