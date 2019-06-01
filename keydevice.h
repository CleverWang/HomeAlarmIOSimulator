#ifndef KEYDEVICE_H
#define KEYDEVICE_H

#include "device.h"

// 按键型设备
class KeyDevice : public Device
{
public:
    KeyDevice(DeviceId deviceId, QObject *device);
};

#endif // KEYDEVICE_H
