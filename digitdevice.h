#ifndef DIGITDEVICE_H
#define DIGITDEVICE_H

#include "device.h"

// 数字型设备
class DigitDevice : public Device
{
public:
    DigitDevice(DeviceId deviceId, QObject *device);
};

#endif // DIGITDEVICE_H
